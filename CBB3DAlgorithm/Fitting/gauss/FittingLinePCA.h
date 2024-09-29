#ifndef FITTINGLINEPCA_H_H
#define FITTINGLINEPCA_H_H
#include "../GeometryTypes.h"
#include <vector>

namespace Gauss {
	double F(const Fitting::Line& line, const Point& p);
	double  GetError(const Fitting::Line& line, const std::vector<Eigen::Vector3d>& points);
	
	double FittingPCA(const std::vector<Point>& points, Fitting::Line& line);

}

#endif // !FITTINGLINEPCA_H_H