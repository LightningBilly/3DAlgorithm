#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<coordinate/CoordinateSystem.h>
#include<tests/GeometryTest.h>
#include<MVCParameterization/hw7.h>
using namespace std;

int main() {
	//coordinate_test();
	cout << BasicToolsTest::PointProjectPlane_Test() << endl;
	// mvc_parameterization();
	printf("ok\n");
	return 0;
}