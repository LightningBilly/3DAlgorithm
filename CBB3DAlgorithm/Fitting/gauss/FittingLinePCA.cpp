#include "FittingLinePCA.h"
#include "../FittingBase.h"
#include <Eigen/Dense>

namespace Gauss {
	using namespace Fitting;
	double F(const Line& line, const Point& p) {
		return (p - line.BasePoint).cross(line.Orient).norm();
	}

	double  GetError(const Line& line, const std::vector<Eigen::Vector3d>& points) {
		double error = 0;
		for (auto& p : points) {
			double d = F(line, p);
			error += d * d;
		}

		return error / points.size();
	}

	double FittingPCA(const std::vector<Point>& points, Line& line) {
		auto center = Fitting::getCenter(points);
		std::vector<Point> copyPoints = points;
		Fitting::moveCenter(center, copyPoints);

		Eigen::MatrixX3d A(copyPoints.size(), 3);

		for (int i = 0; i < copyPoints.size(); ++i) {
			A.block<1, 3>(i, 0) = copyPoints[i];
		}
		Eigen::JacobiSVD<Eigen::MatrixX3d> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
		line.Orient = svd.matrixV().block<3, 1>(0, 0);
		line.BasePoint = center;

		return GetError(line, points);
	}
}