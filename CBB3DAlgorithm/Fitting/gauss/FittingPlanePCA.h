#ifndef FITTINGPLANEPCA_H_H
#define FITTINGPLANEPCA_H_H
#include "../GeometryTypes.h"
#include <vector>

namespace Gauss {
	double F(const Fitting::Plane& plane, const Point& p);
	double  GetError(const Fitting::Plane& plane, const std::vector<Eigen::Vector3d>& points);
	double FittingPCA(const std::vector<Point>& points, Fitting::Plane& plane);

}

#endif // !FITTINGPLANEPCA_H_H