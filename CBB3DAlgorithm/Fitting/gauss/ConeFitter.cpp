#include "ConeFitter.h"
#include "GradientConeFitter.h"
#include "FittingCircle2D.h"
#include <cmath>
#include <Eigen/Dense>
#include<iostream>



namespace Gauss {
	// 枚举+梯度下降法求解
	double getSquareCone(Fitting::Cone& cone, const std::vector<Eigen::Vector3d>& points) {
		Point center = Fitting::getCenter(points);
		std::vector<Point> transPoints(points.size());
		std::vector<Point> circlePoints(3);
		Fitting::Circle2D circle2d;
		Fitting::Cone gradientCone;
		Fitting::FittingBase* cfb = new FittingCircle2D();
		Fitting::GradientBase* gfb;
		Fitting::Matrix U;
		double coneErr = -1;
		//int cnt = 0;
		double xstep = 1, ystep = 1;
		double angleStart = 1, angleEnd = 90;

		for (double i = 0; i < 180; i += xstep) {
			double theta = i / 180 * M_PI;
			for (double j = 0; j < 360; j += ystep) {
				double alpha = j / 180 * M_PI;
				Point orient(cos(theta), sin(theta) * cos(alpha), sin(theta) * sin(alpha));
				U = Fitting::getRotationByOrient(orient);
				// 旋转
				for (int k = 0; k < points.size(); ++k) {
					transPoints[k] = U * (points[k] - center);
				}
				// 按照z绝对值排序
				sort(transPoints.begin(), transPoints.end(),
					[](const Point& a, const Point& b)->bool {return abs(a.z()) < abs(b.z()); });
				// 拟合圆
				for (int k = 0; k < 3; ++k) {
					circlePoints[k] = transPoints[k];
					circlePoints[k].z() = 0;
				}
				gradientCone.orient = orient;
				cfb->Fitting(circlePoints, &circle2d);
				for (double a = angleStart; a < angleEnd; ++a) {
					// 设定初值
					gradientCone.r = circle2d.r;
					gradientCone.center = Point(circle2d.center.x(), circle2d.center.y(), 0);
					gradientCone.alpha = a * 2 / 180 * M_PI;
					// 梯度下降法求解
					gfb = new GradientConeFitter(gradientCone);
					auto err = gfb->Descending(transPoints, &gradientCone);
					delete gfb;
					//err /= points.size();
					if (coneErr < 0 || err < coneErr) {
						coneErr = err;

						// 旋转回去
						cone = gradientCone;
						cone.center = U.transpose() * cone.center;
					}
					//cnt++;
					//if (cnt % 100 == 0) std::cout <<"1-" << cnt << std::endl;
				}
			}
		}
		delete cfb;


		if (cone.r < 0) {
			cone.r *= -1;
			cone.orient *= -1;
		}
		cone.center += center;
		cone.t = cone.r * cos(cone.alpha / 2);

		return coneErr;
	}
}


namespace Gauss {
	double F(Fitting::Cone cone, const Point& p)
	{
		Point dir = p - cone.center;
		double ei = dir.cross(cone.orient).norm();
		double fi = cone.orient.dot(dir);
		double di = ei * cos(cone.alpha / 2) + fi * sin(cone.alpha / 2) - cone.r * cos(cone.alpha / 2);
		return di;
	}
	double GetError(Fitting::Cone cone, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			double d = F(cone, p);
			err += d * d;
		}
		err /= points.size();
		return err;
	}
	Fitting::Matrix ConeFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		double cosA2 = cos(cone.alpha / 2);
		double sinA2 = sin(cone.alpha / 2);
		Fitting::Matrix J(n, 6);
		for (int i = 0; i < n; ++i) {
			auto& p = points[i];
			double ri = Eigen::Vector2d(p.x(), p.y()).norm();

			//di求导
			J(i, 0) = -p.x()*cosA2 / ri;
			J(i, 1) = -p.y()*cosA2 / ri;
			J(i, 2) = -p.x() * p.z()*cosA2 / ri + p.x()*sinA2;
			J(i, 3) = -p.y() * p.z() * cosA2 / ri + p.y() * sinA2;
			J(i, 4) = (-ri*sinA2 + p.z()*cosA2)/2;
			J(i, 5) = -1;
		}
		return J;
	}

	void ConeFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(cone.orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - cone.center);
		}
	}
	void ConeFitter::afterHook(const Eigen::VectorXd& xp)
	{
		cone.center += U.transpose() * Eigen::Vector3d(xp(0), xp(1), -xp(2) * xp(0) - xp(3) * xp(1));
		cone.orient = U.transpose() * Eigen::Vector3d(xp(2), xp(3), 1).normalized();
		cone.alpha += xp(4);
		cone.t += xp(5);
		cone.r = cone.t / cos(cone.alpha / 2);
	}
	Eigen::VectorXd ConeFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		Eigen::VectorXd D(points.size());
		double cosA2 = cos(cone.alpha / 2);
		double sinA2 = sin(cone.alpha / 2);
		double t = cone.r * cosA2;
		for (int i = 0; i < points.size(); ++i)
			D(i) = Eigen::Vector2d(points[i].x(), points[i].y()).norm() * cosA2 + points[i].z() * sinA2 - t;

		return D;
	}


	bool ConeFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 6)return false;
		double err;
		Fitting::Cone initCone;
		err = getSquareCone(initCone, points);
		cone = initCone;

		if (err < 0)return false;

		return true;
	}
	double ConeFitter::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(cone, p);
	}
	double ConeFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(cone, points);
	}
	void ConeFitter::Copy(void* ele)
	{
		memcpy(ele, &cone, sizeof(Fitting::Cone));
	}
}
