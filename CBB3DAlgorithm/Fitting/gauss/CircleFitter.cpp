#include "CircleFitter.h"
#include "FittingPlanePCA.h"
#include "FittingPlane.h"
#include "FittingCircle2D.h"
#include <Eigen/Dense>


namespace Gauss {
	double F(Fitting::Circle circle, const Point& p)
	{
		double ei = (p - circle.center).dot(circle.orient);
		double fi = (p - circle.center).cross(circle.orient).norm() - circle.r;
		return sqrt(ei * ei + fi * fi);
	}
	double GetError(Fitting::Circle circle, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			double d = F(circle, p);
			err += d * d;
		}
		err /= points.size();
		return err;
	}
	Fitting::Matrix CircleFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Fitting::Matrix J(2 * n, 6);
		for (int i = 0; i < n; ++i) {
			auto& p = points[i];

			//ei求导
			double ri = p.norm();
			J(i, 0) = 0;
			J(i, 1) = 0;
			J(i, 2) = -1;
			J(i, 3) = p.x();
			J(i, 4) = p.y();
			J(i, 5) = 0;

			//fi求导
			J(i + n, 0) = -p.x() / ri;
			J(i + n, 1) = -p.y() / ri;
			J(i + n, 2) = 0;
			J(i + n, 3) = -p.x() * p.z() / ri;
			J(i + n, 4) = -p.y() * p.z() / ri;
			J(i + n, 5) = -1;
		}
		return J;
	}

	void CircleFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(circle.orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - circle.center);
		}
	}
	void CircleFitter::afterHook(const Eigen::VectorXd& xp)
	{
		circle.center += U.transpose() * Eigen::Vector3d(xp(0), xp(1), xp(2));
		circle.orient = U.transpose() * Eigen::Vector3d(xp(3), xp(4), 1).normalized();
		circle.r += xp(5);
	}
	Eigen::VectorXd CircleFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Eigen::VectorXd D(2*points.size());
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			// ei
			D(i) = p.z();

			//fi
			D(i + n) = p.norm() - circle.r;
		}
		return D;
	}
	bool CircleFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 3)return false;
		// 拟合平面
		Fitting::Plane plane; 
		Fitting::FittingBase* fb=0;
		/*fb = new FittingPlane();
		double err = fb->Fitting(points, &plane);
		delete fb;
		if(err<0)return false;*/
		FittingPCA(points, plane);

		// 投影到平面，并旋转致xoy平面
		U = Fitting::getRotationByOrient(plane.Orient);
		transPoints.resize(points.size());
		for (int i = 0; i < points.size(); ++i) {
			auto p = points[i];
			double d = (plane.BasePoint - p).dot(plane.Orient);
			p += d * plane.Orient;
			transPoints[i] = U * (p - plane.BasePoint);
		}

		// 拟合圆
		Fitting::Circle2D circle2d;
		fb = new FittingCircle2D();
		fb->Fitting(transPoints, &circle2d);
		delete fb;

		// 旋转回来
		circle.center = U.transpose() * Eigen::Vector3d(circle2d.center.x(), circle2d.center.y(), 0) + plane.BasePoint;
		circle.orient = plane.Orient;
		circle.r = circle2d.r;
		
		return true;
	}
	double CircleFitter::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(circle, p);
	}
	double CircleFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(circle, points);
	}
	void CircleFitter::Copy(void* ele)
	{
		memcpy(ele, &circle, sizeof(Fitting::Circle));
	}
}
