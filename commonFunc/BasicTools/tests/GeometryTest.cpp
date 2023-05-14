#include "GeometryTest.h"
#include "Math/Geometry.h"
#include <iostream>

using namespace std;

int BasicToolsTest::PointProjectPlane_Test() {
	Eigen::Vector3d p(1,2,3);
	Eigen::Vector3d pInPlane(6,8,9.3);
	Eigen::Vector3d normal(3, 10, 6);
	normal.normalize();
	cout << (p - pInPlane).dot(normal) << endl;
	BasicTools::PointProjectPlane(p, pInPlane, normal);

	cout << (p - pInPlane).dot(normal) << endl;

	return 0;
}