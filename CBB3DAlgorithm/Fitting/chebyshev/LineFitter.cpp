#include "LineFitter.h"
#include <algorithm>
#include <Eigen/Dense>


namespace Chebyshev {
	double LineFitter::F(Fitting::Line2D line, const Point& p)
	{
		auto de = Eigen::Vector2d(p.x(), p.y()) - line.BasePoint;
		return abs(de.x() * line.Orient.y() - de.y() * line.Orient.x());
	}

	double LineFitter::GetError(Fitting::Line2D line, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			err = std::max(err, F(line, p));
		}

		return err;
	}

	Fitting::Matrix LineFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 2);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			J(i, 0) = -1;
			J(i, 1) = -p.y();
		}
		return J;
	}

	void LineFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U.setIdentity();
		U(0, 0) = line.Orient.y();
		U(0, 1) = -line.Orient.x();
		U(1, 0) = line.Orient.x();
		U(1, 1) = line.Orient.y();
		Point kBasePt(line.BasePoint.x(), line.BasePoint.y(), 0);
		for (int i = 0; i < points.size(); ++i)transPoints[i] = U * (points[i] - kBasePt);
	}

	void LineFitter::afterHook(const Eigen::VectorXd& xp)
	{
		Point bp = U.transpose() * Point(xp(0), -xp(0) * xp(1), 0);
		line.BasePoint += Eigen::Vector2d(bp.x(), bp.y());
		bp = U.transpose() * Point(xp(1), 1, 0).normalized();
		line.Orient = Eigen::Vector2d(bp.x(), bp.y());
		gamma -= xp(2);
	}
	Eigen::VectorXd LineFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = points[i].x();
		return D;
	}
	bool LineFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 2)return false;
		gamma = -1;
		// 枚举任意两点，选取误差最小的直线
		for (int i = 0; i < points.size(); ++i) {
			for (int j = i + 1; j < points.size(); ++j) {
				Fitting::Line2D tline;
				tline.BasePoint = { points[i].x(), points[i].y() };
				tline.Orient = { points[i].x() - points[j].x(), points[i].y() - points[j].y() };
				tline.Orient.normalize();
				double err = GetError(tline, points);
				if (gamma < 0 || err < gamma) {
					gamma = err;
					line = tline;
				}
			}
		}
		return true;
	}
	double LineFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::LineFitter::F(line, p);
	}
	double LineFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::LineFitter::GetError(line, points);
	}
	void LineFitter::Copy(void* ele)
	{
		memcpy(ele, &line, sizeof(Fitting::Line2D));
	}
	LineFitter::LineFitter()
	{
		ft = Fitting::FittingType::CHEBYSHEV;
	}
}


// 凸包旋转卡壳算法
namespace Chebyshev {
	using namespace std;
	const int M = 1e6 + 10;

	const double eps = 1e-6;
	using Point2d = Eigen::Vector2d;

	double operator^ (const Point2d& p1, const Point2d& p2) {
		return p1.x() * p2.y() - p1.y() * p2.x();
	}

	Point2d points[M];
	Point2d lowPoint;
	int st[M], top;

	bool cmp(Point2d p1, Point2d p2) {
		p1 = p1 - lowPoint;
		p2 = p2 - lowPoint;

		double xmult = p1 ^ p2; // 求叉积
		if (abs(xmult) > eps) {
			return xmult > 0;
		}

		return p1.norm() < p2.norm();
	}

	void graham(int n) {
		lowPoint = points[0];
		for (int j = 0; j < n; ++j) {
			if (points[j].y() < lowPoint.y() || (points[j].y() == lowPoint.y() && points[j].x() < lowPoint.x())) lowPoint = points[j];
		}
		sort(points, points + n, cmp);
		top = 2;
		st[0] = 0;
		st[1] = 1;

		for (int i = 2; i < n; ++i) {
			while (top > 2 && ((points[st[top - 1]] - points[st[top - 2]]) ^ (points[i] - points[st[top - 1]])) <= eps)top--;
			st[top++] = i;
		}
	}

	double rotate(Fitting::Line2D& line) {
		double err = -1;
		st[top] = st[0]; // 将第一点连接后最后，作为最后一条边的终点
		int up = 1;

		for (int i = 0; i < top; ++i) {
			Point2d bottom = points[st[i + 1]] - points[st[i]];
			bottom.normalize();
			// 以i, i+1 线段为底
			// 查看顶部最高点, 发现下一个点比当前点高，就+1
			while (abs(bottom ^ (points[st[up]] - points[st[i]])) < abs(bottom ^ (points[st[up + 1]] - points[st[i]]))) up = (up + 1) % top;
			double d = abs((points[st[up]] - points[st[i]]) ^ bottom);
			if (err < 0 || d < err) {
				err = d;
				line.BasePoint = points[st[up]] + points[st[i]];
				line.BasePoint /= 2;
				line.Orient = bottom;
			}
		}

		return err;
	}

	double ConvexRotateFitting(const std::vector<Eigen::Vector3d>& point3ds, Fitting::Line2D& line)
	{
		for (int i = 0; i < point3ds.size(); ++i) points[i] = Point2d(point3ds[i].x(), point3ds[i].y());
		graham(point3ds.size());
		double err = rotate(line);
		return err/2;
	}
}