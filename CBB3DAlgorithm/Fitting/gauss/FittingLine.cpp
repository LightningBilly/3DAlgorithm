#include "FittingLine.h"
#include "FittingLinePCA.h"


namespace Gauss {
	Fitting::Matrix FittingLine::Jacobi(const std::vector<Eigen::Vector3d>& points)
	{
		Fitting::Matrix J(points.size(), 4);
		for (int i = 0; i < points.size(); ++i) {
			auto& p = points[i];
			double r = Eigen::Vector2d(p.x(), p.y()).norm();
			J(i, 0) = -p.x() / r;
			J(i, 1) = -p.y() / r;
			J(i, 2) = -p.x() * p.z() / r;
			J(i, 3) = -p.y() * p.z() / r;
		}
		return J;
	}
	void FittingLine::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(line.Orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - line.BasePoint);
		}
	}
	void FittingLine::afterHook(const Eigen::VectorXd& xp)
	{
		line.BasePoint += U.transpose() * Eigen::Vector3d(xp(0), xp(1), -xp(0)*xp(2)-xp(1)*xp(3));
		line.Orient =U.transpose()* Eigen::Vector3d(xp(2), xp(3), 1).normalized();
	}
	Eigen::VectorXd FittingLine::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) = points[i].norm();
		return D;
	}
	bool FittingLine::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		if (points.size() < 2)return false;
		line.BasePoint = points[0];
		Point s = points[1];
		for (int i = 2; i < points.size(); ++i)
			if ((line.BasePoint - points[i]).norm() > (line.BasePoint - s).norm())s = points[i];

		line.Orient = line.BasePoint - s;
		line.Orient.normalize();

		return true;
	}
	double FittingLine::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(line, p);
	}
	double FittingLine::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(line, points);
	}
	void FittingLine::Copy(void* ele)
	{
		memcpy(ele, &line, sizeof(Fitting::Line));
	}
}
