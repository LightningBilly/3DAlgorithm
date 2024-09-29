#include "PlaneFitter.h"
#include "../gauss/FittingPlane.h"
#include <algorithm>
#include <Eigen/Dense>


namespace Chebyshev {
	double PlaneFitter::F(Fitting::Plane plane, const Point& p)
	{
		auto de = p - plane.BasePoint;
		return plane.Orient.dot(de);
	}

	double PlaneFitter::GetError(Fitting::Plane plane, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) { 
			err = std::max(err, abs(F(plane, p)));
		}

		return err;
	}

	Fitting::Matrix PlaneFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 3);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			J(i, 0) = -1;
			J(i, 1) = p.x();
			J(i, 2) = p.y();
		}
		return J;
	}

	void PlaneFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(plane.Orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - plane.BasePoint);
		}
	}

	void PlaneFitter::afterHook(const Eigen::VectorXd& xp)
	{
		plane.BasePoint += U.transpose() * Eigen::Vector3d(xp(0) * xp(1), xp(0) * xp(2), xp(0));
		plane.Orient = U.transpose() * Eigen::Vector3d(xp(1), xp(2), 1).normalized();
		gamma -= xp(3);
	}
	Eigen::VectorXd PlaneFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = points[i].z();
		return D;
	}
	bool PlaneFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 3)return false;
		Fitting::FittingBase* fb = new Gauss::FittingPlane();
		fb->Fitting(points, &plane);
		delete fb;

		gamma = GetError(plane, points);
		return true;
	}
	double PlaneFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::PlaneFitter::F(plane, p);
	}
	double PlaneFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::PlaneFitter::GetError(plane, points);
	}
	void PlaneFitter::Copy(void* ele)
	{
		memcpy(ele, &plane, sizeof(Fitting::Plane));
	}
	PlaneFitter::PlaneFitter()
	{
		ft = Fitting::FittingType::CHEBYSHEV;
	}
}
