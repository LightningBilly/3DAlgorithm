#include "MaxInCircleFitter.h"
#include "../gauss/FittingCircle2D.h"
#include <Eigen/Dense>


namespace Chebyshev {
	double F(Fitting::Circle2D circle, const Point& p)
	{
		return Eigen::Vector2d(p.x() - circle.center.x(), p.y() - circle.center.y()).norm();
	}

	double GetError(Fitting::Circle2D circle, const std::vector<Eigen::Vector3d>& points)
	{
		double err = -1;
		for (auto& p : points) {
			double d = F(circle, p);
			if (err < 0 || d < err) err = d;
		}

		return err;
	}
	Fitting::Matrix MaxInCircleFitter::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 2);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			double ri = F(p);
			J(i, 0) = -(p.x() - circle.center.x()) / ri;
			J(i, 1) = -(p.y() - circle.center.y()) / ri;
		}
		return J;
	}

	void MaxInCircleFitter::afterHook(const Eigen::VectorXd& xp)
	{
		circle.center += Eigen::Vector2d(xp(0), xp(1));
		circle.r += xp(2);
		gamma = circle.r;
	}
	Eigen::VectorXd MaxInCircleFitter::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = F(points[i]);
		return D;
	}
	bool MaxInCircleFitter::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 3)return false;

		Fitting::FittingBase* fb = new Gauss::FittingCircle2D();
		auto err = fb->Fitting(points, &circle);
		delete fb;
		if (err < 0)return false;
		// ¼ÆËãgamma
		gamma = GetError(points);
		circle.r = gamma;
		return true;
	}
	double MaxInCircleFitter::F(const Eigen::Vector3d& p)
	{
		return Chebyshev::F(circle, p);
	}
	double MaxInCircleFitter::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Chebyshev::GetError(circle, points);
	}
	void MaxInCircleFitter::Copy(void* ele)
	{
		memcpy(ele, &circle, sizeof(Fitting::Circle2D));
	}
	MaxInCircleFitter::MaxInCircleFitter()
	{
		ft = Fitting::FittingType::MAXIN;
	}
}
