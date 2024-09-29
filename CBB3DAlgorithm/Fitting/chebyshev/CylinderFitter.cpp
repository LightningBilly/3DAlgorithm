#include "CylinderFitter.h"
#include "../gauss/CylinderFitter.h"
#include <cmath>
#include <Eigen/Dense>
#include<iostream>


namespace Chebyshev {
	double CylinderFitter::F(Fitting::Cylinder cylinder, const Point& p)
	{
		double di = (p - cylinder.center).cross(cylinder.orient).norm() - cylinder.r;
		return di;
	}
	double CylinderFitter::GetError(Fitting::Cylinder cylinder, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			err = std::max(err, abs(F(cylinder, p)));
		}

		return err;
	}
	Fitting::Matrix CylinderFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Fitting::Matrix J(n, 5);
		for (int i = 0; i < n; ++i) {
			auto& p = points[i];
			double ri = Eigen::Vector2d(p.x(), p.y()).norm();

			//diÇóµ¼
			J(i, 0) = -p.x() / ri;
			J(i, 1) = -p.y() / ri;
			J(i, 2) = -p.x() * p.z() / ri;
			J(i, 3) = -p.y() * p.z() / ri;
			J(i, 4) = -1;
		}
		return J;
	}

	void CylinderFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(cylinder.orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - cylinder.center);
		}
	}
	void CylinderFitter::afterHook(const Eigen::VectorXd& xp)
	{
		cylinder.center += U.transpose() * Eigen::Vector3d(xp(0), xp(1), -xp(2)*xp(0)-xp(3)*xp(1));
		cylinder.orient = U.transpose() * Eigen::Vector3d(xp(2), xp(3), 1).normalized();
		cylinder.r += xp(4);
		gamma -= xp(5);
	}
	Eigen::VectorXd CylinderFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i) D(i) = Eigen::Vector2d(points[i].x(), points[i].y()).norm() - cylinder.r;
		return D;
	}
	bool CylinderFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 5)return false;
		Fitting::FittingBase* fb = new Gauss::CylinderFitter();
		fb->Fitting(points, &cylinder);
		delete fb;
		gamma = GetError(points);
		return true;
	}
	double CylinderFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::CylinderFitter::F(cylinder, p);
	}
	double CylinderFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::CylinderFitter::GetError(cylinder, points);
	}
	void CylinderFitter::Copy(void* ele)
	{
		memcpy(ele, &cylinder, sizeof(Fitting::Cylinder));
	}

	CylinderFitter::CylinderFitter()
	{
		ft = Fitting::FittingType::CHEBYSHEV;
	}
}
