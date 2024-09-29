#include "CircleFitter.h"
#include "../gauss/FittingCircle2D.h"
#include <algorithm>
#include <Eigen/Dense>


namespace Chebyshev {
	double CircleFitter::F(Fitting::Circle2D circle, const Point& p)
	{
		auto de = Eigen::Vector2d(p.x(), p.y()) - circle.center;
		return de.norm() - circle.r;
	}

	double CircleFitter::GetError(Fitting::Circle2D circle, const std::vector<Eigen::Vector3d>& points)
	{
		double err = 0;
		for (auto& p : points) {
			err = std::max(err, abs(F(circle, p)));
		}

		return err;
	}

	Fitting::Matrix CircleFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 3);
		for (int i = 0; i < points.size(); ++i) {
			Eigen::Vector2d p = { points[i].x() - circle.center.x(),points[i].y() - circle.center.y() };
			J(i, 0) = -p.x() / p.norm();
			J(i, 1) = -p.y() / p.norm();
			J(i, 2) = -1;
		}
		return J;
	}

	void CircleFitter::beforHook(const std::vector<Eigen::Vector3d>& points)
	{}

	void CircleFitter::afterHook(const Eigen::VectorXd& xp)
	{
		circle.center += Eigen::Vector2d(xp(0), xp(1));
		circle.r += xp(2);
		gamma -= xp(3);
	}
	Eigen::VectorXd CircleFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = F(circle, points[i]);
		return D;
	}
	bool CircleFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 3)return false;
		Fitting::FittingBase* fb = new Gauss::FittingCircle2D();
		fb->Fitting(points, &circle);
		delete fb;

		gamma = GetError(circle, points);
		return true;
	}
	double CircleFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::CircleFitter::F(circle, p);
	}
	double CircleFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::CircleFitter::GetError(circle, points);
	}
	void CircleFitter::Copy(void* ele)
	{
		memcpy(ele, &circle, sizeof(Fitting::Circle2D));
	}
	CircleFitter::CircleFitter()
	{
		ft = Fitting::FittingType::CHEBYSHEV;
	}
}
