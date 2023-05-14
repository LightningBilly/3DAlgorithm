//
// Created by chenbinbin on 2022/3/22.
//

#include "CoordinateSystemTest.h"
#include "CoordinateSystem.h"
#include "include/Math/MMatrix3.h"
#include <fstream>
#include <iostream>
#include <include/Math/Geometry.h>
using namespace std;

namespace CoordinateSystem {
	void coordinate_test_1() {

		cout << "coordinate_test1" << endl;

		Point p(0, 0, 0);
		Point line_start(0, 0, 0);
		Point line_end(1, 0, 0);
		Point plane_normal(0, 1, 0);
		Point plane_point(0, 0, 0);
		plane_normal.normalize();
		CoordinateOrient line_orient = CoordinateOrient::X;
		CoordinateOrient normal_orient = CoordinateOrient::Y;
		auto corrd = GenerateCoordinate(p, line_start, line_end, plane_normal, plane_point,
			line_orient, normal_orient);

		cout << corrd.mat << endl;
		cout << corrd.trans << endl;
	}


	void coordinate_test_2() {

		cout << "coordinate_test2" << endl;

		Point p(1, 123, 444);
		Point line_start(1, 23, 9);
		Point line_end(33, 2, 35);
		Point plane_normal(12, 44, 22);
		Point plane_point(0, 0, 0);
		plane_normal.normalize();
		CoordinateOrient line_orient = CoordinateOrient::X;
		CoordinateOrient normal_orient = CoordinateOrient::Y;
		auto corrd = GenerateCoordinate(p, line_start, line_end, plane_normal, plane_point,
			line_orient, normal_orient);

		cout << corrd.mat << endl;
		cout << corrd.trans << endl;
		line_end -= line_start;


		BasicTools::PointProjectPlane(line_end, plane_point, plane_normal);
		line_end.normalize();
		cout << "直线投影向量: " << line_end << endl;
		cout << "面法向: " << plane_normal << endl;
		cout << "第三第轴: " << line_end.cross(plane_normal) << endl;
	}


	void coordinate_test_3() {

		cout << "coordinate_test3" << endl;

		Point p(1, 123, 444);
		Point line_start(0, 0, 0);
		Point line_end(0, 0, 0);
		Point plane_normal(12, 44, 22);
		Point plane_point(0, 0, 0);
		plane_normal.normalize();
		CoordinateOrient line_orient = CoordinateOrient::X;
		CoordinateOrient normal_orient = CoordinateOrient::Y;
		auto corrd = GenerateCoordinate(p, line_start, line_end, plane_normal, plane_point,
			line_orient, normal_orient);

		cout << corrd.mat << endl;
		cout << corrd.trans << endl;
		line_end -= line_start;


		BasicTools::PointProjectPlane(line_end, plane_point, plane_normal);
		line_end.normalize();
		cout << "直线投影向量: " << line_end << endl;
		cout << "面法向: " << plane_normal << endl;
		cout << "第三第轴: " << line_end.cross(plane_normal) << endl;
	}


	void coordinate_test()
	{
		coordinate_test_1();
		coordinate_test_2();
		coordinate_test_3();
	}

	void coordinatert_test() {
		cout << "coordinaterttest" << endl;
	}
}