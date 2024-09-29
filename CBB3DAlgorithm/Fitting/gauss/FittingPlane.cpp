#include "FittingPlane.h"
#include "FittingPlanePCA.h"
#include <Eigen/Dense>


namespace Gauss {
	Fitting::Matrix FittingPlane::Jacobi(const std::vector<Eigen::Vector3d>& points)
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
	void FittingPlane::beforHook(const std::vector<Eigen::Vector3d>& points)
	{
		U = Fitting::getRotationByOrient(plane.Orient);
		for (int i = 0; i < points.size(); ++i) {
			transPoints[i] = U * (points[i] - plane.BasePoint);
		}
	}
	void FittingPlane::afterHook(const Eigen::VectorXd& xp)
	{
		plane.BasePoint += U.transpose() * Eigen::Vector3d(xp(0)*xp(1), xp(0)*xp(2), xp(0));
		plane.Orient =U.transpose()* Eigen::Vector3d(xp(1), xp(2), 1).normalized();
	}
	Eigen::VectorXd FittingPlane::getDArray(const std::vector<Eigen::Vector3d>& points)
	{
		Eigen::VectorXd D(points.size());
		for (int i = 0; i < points.size(); ++i)D(i) =points[i].z();
		return D;
	}
	bool FittingPlane::GetInitFit(const std::vector<Eigen::Vector3d>& points)
	{
		int n = points.size();
		if (n < 3)return false;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				for (int k = 0; k < j; ++k) {
					// 判断两边之和大于第三边
					double l1 = (points[i] - points[j]).norm();
					double l2 = (points[i] - points[k]).norm();
					double l3 = (points[j] - points[k]).norm();
					double eps = 1;
					if (l1 + l2 - l3 - eps < 0)continue;
					if (l1 + l3 - l2 - eps < 0)continue;
					if (l3 + l2 - l1 - eps < 0)continue;

					plane.BasePoint = points[i];
					plane.Orient = (points[j] - plane.BasePoint).cross(points[k] - plane.BasePoint);
					plane.Orient.normalize();

					return true;
				}
			}
		}


		return false;
	}
	double FittingPlane::F(const Eigen::Vector3d& p)
	{
		return Gauss::F(plane, p);
	}
	double FittingPlane::GetError(const std::vector<Eigen::Vector3d>& points)
	{
		return Gauss::GetError(plane, points);
	}
	void FittingPlane::Copy(void* ele)
	{
		memcpy(ele, &plane, sizeof(Fitting::Plane));
	}
}
