#include "SphereFitter.h"
#include "../gauss/SphereFitter.h"
#include <algorithm>
#include <Eigen/Dense>


namespace Chebyshev {
	double SphereFitter::F(Fitting::Sphere sphere, const Point& p)
	{
		auto de = p - sphere.center;
		return de.norm() - sphere.r;
	}

	double SphereFitter::GetError(Fitting::Sphere sphere, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			err = std::max(err, abs(F(sphere, p)));
		}

		return err;
	}

	Fitting::Matrix SphereFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 4);
		for (int i = 0; i < points.size(); ++i) {
			auto  p =  points[i] - sphere.center;
			J(i, 0) = -p.x() / p.norm();
			J(i, 1) = -p.y() / p.norm();
			J(i, 2) = -p.z() / p.norm();
			J(i, 3) = -1;
		}
		return J;
	}

	void SphereFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{}

	void SphereFitter::afterHook(const Eigen::VectorXd& xp)
	{
		sphere.center += Eigen::Vector3d(xp(0), xp(1), xp(2));
		sphere.r += xp(3);
		gamma -= xp(4);
	}
	Eigen::VectorXd SphereFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = F(sphere, points[i]);
		return D;
	}
	bool SphereFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 4)return false;
		Fitting::FittingBase* fb = new Gauss::SphereFitter();
		fb->Fitting(points, &sphere);
		delete fb;

		gamma = GetError(sphere, points);
		return true;
	}
	double SphereFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::SphereFitter::F(sphere, p);
	}
	double SphereFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::SphereFitter::GetError(sphere, points);
	}
	void SphereFitter::Copy(void* ele)
	{
		memcpy(ele, &sphere, sizeof(Fitting::Sphere));
	}
	SphereFitter::SphereFitter()
	{
		ft = Fitting::FittingType::CHEBYSHEV;
	}
}
