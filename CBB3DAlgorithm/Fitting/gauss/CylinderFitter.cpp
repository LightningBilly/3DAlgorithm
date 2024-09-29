#include "CylinderFitter.h"
#include "CircleFitter.h"
#include <cmath>
#include <Eigen/Dense>
#include<iostream>


namespace Gauss {
	double F(Fitting::Cylinder cylinder, const Point& p)
	{
		double di = (p - cylinder.center).cross(cylinder.orient).norm() - cylinder.r;
		return di;
	}
	double GetError(Fitting::Cylinder cylinder, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			double d = F(cylinder, p);
			err += d * d;
		}
		err /= points.size();
		return err;
	}
	Fitting::Matrix CylinderFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Fitting::Matrix J(n, 5);
		for (int i = 0; i < n; ++i) {
			auto& p = points[i];
			double ri = Eigen::Vector2d(p.x(), p.y()).norm();

			//di求导
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
		double cylinerErr = -1;
		transPoints.resize(points.size());
		Point center = Fitting::getCenter(points);
		// 拟合平面
		Fitting::FittingBase* fb = new CircleFitter();
		Fitting::Circle cir;
		int cnt = 0;
		for (double i = 0; i < 180; ++i) {
			double theta = i / 180 * M_PI;
			for (double j = 0; j < 180; ++j) {
				double alpha = j / 180 * M_PI;
				Point orient(cos(theta) , sin(theta)*cos(alpha),sin(theta)*sin(alpha));
				// 投影平面
				for (int k = 0; k < points.size(); ++k) {
					double d = (center-points[k]).dot(orient);
					transPoints[k] = points[k] + d * orient;
				}

				// 拟合圆
				double err = fb->Fitting(transPoints, &cir);
				if (err>0 && (cylinerErr < 0 || err < cylinerErr)) {
					//std::cout << "error : "<< err << std::endl;
					cylinerErr = err;
					cylinder.center = cir.center;
					cylinder.orient = cir.orient;
					cylinder.r = cir.r;
				}
				//cnt++;
				//if(cnt%100==0) std::cout << cnt << std::endl;

			}
			if (cylinerErr < 1e-4)break;
		}
		delete fb;
		return true;
	}
	double CylinderFitter::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(cylinder, p);
	}
	double CylinderFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(cylinder, points);
	}
	void CylinderFitter::Copy(void* ele)
	{
		memcpy(ele, &cylinder, sizeof(Fitting::Cylinder));
	}
}
