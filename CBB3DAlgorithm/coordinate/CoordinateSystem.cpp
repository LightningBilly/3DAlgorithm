//
// Created by chenbinbin on 2022/3/22.
//

#include "CoordinateSystem.h"
#include <fstream>
#include <iostream>
#include <Eigen/Sparse>
#include <include/Math/Geometry.h>
using namespace std;
using namespace Eigen;



RigidRTMatrix GenerateCoordinate(const Point& p, const Point& line_start,
	const Point& line_end, const Point& plane_normal, const Point& plane_point,
	CoordinateOrient line_orient, CoordinateOrient normal_orient) {
	cout << "GenerateCoordinate" << endl;
	RigidRTMatrix coord;
	// 1.计算线段投影的单位向量。
	Point project_line_start = line_start;
	BasicTools::PointProjectPlane(project_line_start, plane_point, plane_normal);

	Point project_line_end = line_end;
	BasicTools::PointProjectPlane(project_line_end, plane_point, plane_normal);
	Point project_vec = (project_line_end - project_line_start).normalized();
	assert(project_vec.squaredNorm() > 1e-6);

	coord.mat.block<1, 3>(line_orient, 0) = project_vec;


		// 2.根据输入要求确定坐标系的两个轴。
		// 3.根据已经确定的两轴计算剩下的一轴。
		// 4.确定原点。

	return RigidRTMatrix();
}


void coordinate_test()
{
	cout << "coordinate_test2" << endl;
	Point p(0, 0, 0);
	Point line_start(1,2,3);
	Point line_end(7, 8, 9);
	Point plane_normal(9, 8, 10);
	Point plane_point(10, 10, 10);
	CoordinateOrient line_orient = CoordinateOrient::X;
	CoordinateOrient normal_orient = CoordinateOrient::Y;
	GenerateCoordinate(p, line_start, line_end, plane_normal, plane_point,
		line_orient, normal_orient);
}