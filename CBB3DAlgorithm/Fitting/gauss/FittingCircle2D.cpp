#include "FittingCircle2D.h"
#include <Eigen/Dense>


namespace Gauss {
	double F(Fitting::Circle2D circle, const Point& p)
	{
		double ri = Eigen::Vector2d(p.x() - circle.center.x(), p.y() - circle.center.y()).norm();
		return ri-circle.r;
	}
	double GetError(Fitting::Circle2D circle, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			double d = F(circle, p);
			err += d * d;
		}
		err /= points.size();
		return err;
	}
	Fitting::Matrix FittingCircle2D::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 3);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			double ri = (Eigen::Vector2d(p.x(), p.y()) - circle.center).norm();
			J(i, 0) = -(p.x()-circle.center.x())/ri;
			J(i, 1) = -(p.y() - circle.center.y()) / ri;
			J(i, 2) = -1;
		}
		return J;
	}

	void FittingCircle2D::afterHook(const Eigen::VectorXd& xp)
	{
		circle.center += Eigen::Vector2d(xp(0), xp(1));
		circle.r += xp(2);
	}
	Eigen::VectorXd FittingCircle2D::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) =F(points[i]);
		return D;
	}
	bool FittingCircle2D::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 3)return false;
		Fitting::Matrix A(points.size(), 3);
		Eigen::VectorXd B(points.size());

		for (int i = 0; i < points.size(); ++i) {
			A(i, 0) = 2 * points[i].x();
			A(i, 1) = 2 * points[i].y();
			A(i, 2) = -1;

			B(i) = Eigen::Vector2d(points[i].x(), points[i].y()).squaredNorm();
		}
		Eigen::VectorXd xp;
		// Çó½â Axp = B  https://blog.csdn.net/ABC_ORANGE/article/details/104489257/
		xp = A.colPivHouseholderQr().solve(B);
		circle.center.x() = xp(0);
		circle.center.y() = xp(1);
		circle.r = sqrt(circle.center.squaredNorm() - xp(2));

		return true;
	}
	double FittingCircle2D::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(circle, p);
	}
	double FittingCircle2D::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(circle, points);
	}
	void FittingCircle2D::Copy(void* ele)
	{
		memcpy(ele, &circle, sizeof(Fitting::Circle2D));
	}
}
