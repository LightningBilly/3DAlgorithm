//
// Created by chenbinbin on 2022/3/22.
//

#ifndef MESHWORK_COORDINATE_H
#define MESHWORK_COORDINATE_H

#include <include/Math/MMatrix3.h>

using namespace acamcad;
enum CoordinateOrient {
	X=0,Y=1,Z=2
};

RigidRTMatrix GenerateCoordinate(const Point& p, const Point& line_start,
	const Point& line_end, const Point& plane_normal, const Point& plane_point,
	CoordinateOrient line_orient, CoordinateOrient normal_orient);

void coordinate_test();

#endif //MESHWORK_COORDINATE_H
