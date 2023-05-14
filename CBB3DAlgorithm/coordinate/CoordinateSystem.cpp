//
// Created by chenbinbin on 2022/3/22.
//

#include "CoordinateSystem.h"
#include <fstream>
#include <iostream>
#include <Eigen/Sparse>
#include <include/Math/Geometry.h>
#include<assert.h>
using namespace std;
using namespace Eigen;



RigidRTMatrix GenerateCoordinate(const Point& p, const Point& line_start,
	const Point& line_end, const Point& plane_normal, const Point& plane_point,
	CoordinateOrient line_orient, CoordinateOrient normal_orient) {
	cout << "GenerateCoordinate" << endl;
	assert(abs(plane_normal.squaredNorm() - 1) < 1e-6);
	RigidRTMatrix coord;
	// 1.计算线段投影的单位向量。
	Point project_line_start = line_start;
	BasicTools::PointProjectPlane(project_line_start, plane_point, plane_normal);

	Point project_line_end = line_end;
	BasicTools::PointProjectPlane(project_line_end, plane_point, plane_normal);
	Point project_vec = (project_line_end - project_line_start).normalized();
	assert(project_vec.squaredNorm() > 1e-4);
	cout <<( project_vec.squaredNorm() > 1e-4) << endl;

	coord.mat.block<1, 3>(line_orient, 0) = project_vec;
	// 2.根据输入要求确定坐标系的两个轴。
	coord.mat.block<1, 3>(normal_orient, 0) = plane_normal;
	// 3.根据已经确定的两轴计算剩下的一轴。
	int left = CoordinateOrient::X + CoordinateOrient::Y + CoordinateOrient::Z;
	left -= line_orient + normal_orient;
	coord.mat.block<1, 3>(left, 0) = coord.mat.block<1, 3>((left + 1) % 3, 0).cross(coord.mat.block<1, 3>((left + 2) % 3, 0));

	// 4.确定原点。
	coord.trans = p;

	return coord;
}

RigidRTMatrix Coordinate2RT(const RigidRTMatrix& coord) {
	RigidRTMatrix res;
	RigidRTMatrix RTO;
	RTO.trans = -coord.trans;
	RigidRTMatrix RTOInvers;
	RTOInvers.trans = coord.trans;
	RigidRTMatrix A;
	A.mat = coord.mat.transpose();
	res = A * RTO;
	res = RTOInvers * res;
	return res;
}

