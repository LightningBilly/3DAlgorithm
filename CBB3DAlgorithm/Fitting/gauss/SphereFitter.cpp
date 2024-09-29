#include "SphereFitter.h"
#include <Eigen/Dense>


namespace Gauss {
	double F(Fitting::Sphere sphere, const Point& p)
	{
		double ri = (p-sphere.center).norm();
		return ri-sphere.r;
	}
	double GetError(Fitting::Sphere sphere, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			double d = F(sphere, p);
			err += d * d;
		}
		err /= points.size();
		return err;
	}
	Fitting::Matrix SphereFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 4);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			double ri = (p - sphere.center).norm();
			J(i, 0) = -(p.x() - sphere.center.x()) / ri;
			J(i, 1) = -(p.y() - sphere.center.y()) / ri;
			J(i, 2) = -(p.z() - sphere.center.z()) / ri;
			J(i, 3) = -1;
		}
		return J;
	}

	void SphereFitter::afterHook(const Eigen::VectorXd& xp)
	{
		sphere.center += Eigen::Vector3d(xp(0), xp(1), xp(2));
		sphere.r += xp(3);
	}
	Eigen::VectorXd SphereFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) =F(points[i]);
		return D;
	}
	bool SphereFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 4)return false;
		Fitting::Matrix A(points.size(), 4);
		Eigen::VectorXd B(points.size());

		for (int i = 0; i < points.size(); ++i) {
			A(i, 0) = 2 * points[i].x();
			A(i, 1) = 2 * points[i].y();
			A(i, 2) = 2 * points[i].z();
			A(i, 3) = -1;

			B(i) = points[i].squaredNorm();
		}

		Eigen::VectorXd xp;
		// Çó½â Axp = B  https://blog.csdn.net/ABC_ORANGE/article/details/104489257/
		xp = A.colPivHouseholderQr().solve(B);
		sphere.center.x() = xp(0);
		sphere.center.y() = xp(1);
		sphere.center.z() = xp(2);
		sphere.r = sqrt(sphere.center.squaredNorm() - xp(3));

		return true;
	}
	double SphereFitter::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(sphere, p);
	}
	double SphereFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(sphere, points);
	}
	void SphereFitter::Copy(void* ele)
	{
		memcpy(ele, &sphere, sizeof(Fitting::Sphere));
	}
}
