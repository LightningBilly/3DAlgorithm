#include "FittingPlanePCA.h"
#include "../FittingBase.h"
#include <Eigen/Dense>

namespace Gauss {
	using namespace Fitting;
	double F(const Plane& plane, const Point& p) {
		return (p - plane.BasePoint).dot(plane.Orient);
	}

	double  GetError(const Plane& plane, const std::vector<Eigen::Vector3d>& points) {
		double error = 0;
		for (auto& p : points) {
			double d = F(plane, p);
			error += d * d;
		}

		return error / points.size();
	}


	double FittingPCA(const std::vector<Point>& points, Plane& plane) {
		auto center = Fitting::getCenter(points);
		std::vector<Point> copyPoints = points;
		Fitting::moveCenter(center, copyPoints);

		Eigen::MatrixX3d A(copyPoints.size(), 3);

		for (int i = 0; i < copyPoints.size(); ++i) {
			A.block<1, 3>(i, 0) = copyPoints[i];
		}
		Eigen::JacobiSVD<Eigen::MatrixX3d> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
		plane.Orient = svd.matrixV().block<3, 1>(0, 2);
		plane.BasePoint = center;

		return GetError(plane, points);
	}
}