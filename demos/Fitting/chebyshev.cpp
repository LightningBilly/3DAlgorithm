#include "gauss.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include <Fitting/chebyshev/MaxInCircleFitter.h>
#include <Fitting/chebyshev/LineFitter.h>
#include <Fitting/chebyshev/CircleFitter.h>
#include <Fitting/chebyshev/SphereFitter.h>
#include <Fitting/chebyshev/PlaneFitter.h>
#include <Fitting/chebyshev/CylinderFitter.h>
#include<include/IOType/PointCloud.h>
#include "chebyshev.h"
#include <Fitting/chebyshev/TestAllCase.h>
using namespace std;

// ./FittingRun.exe FittingMaxCircleInTest "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C09.asc"
void  FittingMaxCircleInTest(int argc, char** argv) {
	using namespace Chebyshev;
	std::vector<Eigen::Vector3d> cld;

	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/commonFunc/BasicTools/include/IOType/point.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		//cout << p << endl;
	}
	printf("ok\n");

	Fitting::Circle2D circle;
	Fitting::FittingBase* fb = new Chebyshev::MaxInCircleFitter();
	auto err = fb->Fitting(cld, &circle);
	delete fb;

	cout << "x0:"<< circle.center.x() << endl;
	cout << "y0:"<< circle.center.y() << endl;
	cout << "r:"<< circle.r << endl;
}

// ./FittingRun.exe ConvexLineTest "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C01.asc"
void ConvexLineTest(int argc, char** argv)
{
	using namespace Chebyshev;
	std::vector<Eigen::Vector3d> cld;

	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/commonFunc/BasicTools/include/IOType/point.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		//cout << p << endl;
	}
	printf("ok\n");

	Fitting::Line2D line;

	double err = ConvexRotateFitting(cld, line);

	cout << err << endl;
	cout << line.BasePoint << endl;
	cout << line.Orient<< endl;
}


void chebyshevTestAll(int argc, char** argv) {
	Chebyshev::TestAllCase();
}

// ./FittingRun.exe Chebyshev::LineTest "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C01.asc"
void Chebyshev::LineTest(int argc, char** argv)
{
	std::vector<Eigen::Vector3d> cld;

	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/commonFunc/BasicTools/include/IOType/point.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		//cout << p << endl;
	}
	printf("ok\n");

	Fitting::Line2D line;
	Fitting::FittingBase* fb = new Chebyshev::LineFitter();
	auto err = fb->Fitting(cld, &line);
	delete fb;

	cout << err*2 << endl;
	cout << line.BasePoint << endl;
	cout << line.Orient << endl;
}




//  ./FittingRun.exe  Chebyshev::CircleTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C09.asc"
void Chebyshev::CircleTest(int argc, char** argv) {
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Circle2D circle;
	Fitting::FittingBase* fb = new Chebyshev::CircleFitter();
	auto err = fb->Fitting(cld, &circle);

	cout << err << endl;
	cout << circle.center << endl;
	cout << circle.r << endl;

	delete fb;
}



//  ./FittingRun.exe  Chebyshev::PlaneTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C17.asc"
void Chebyshev::PlaneTest(int argc, char** argv) {
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Plane plane;
	Fitting::FittingBase* fb = new Chebyshev::PlaneFitter();
	auto err = fb->Fitting(cld, &plane);

	cout << err << endl;
	cout << plane.BasePoint << endl;
	cout << plane.Orient << endl;

	delete fb;
}

//  ./FittingRun.exe  Chebyshev::CylinderTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C37.asc"
void Chebyshev::CylinderTest(int argc, char** argv) {
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Cylinder cylinder;
	Fitting::FittingBase* fb = new Chebyshev::CylinderFitter();
	auto err = fb->Fitting(cld, &cylinder);

	cout << err*2 << endl;
	cout << cylinder.center << endl;
	cout << cylinder.orient << endl;
	cout << cylinder.r << endl;

}

//  ./FittingRun.exe  Chebyshev::SphereTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\chebyshev\chebyshev-testdata\officialtest\data\C27.asc"
void Chebyshev::SphereTest(int argc, char** argv) {
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Sphere sphere;
	Fitting::FittingBase* fb = new Chebyshev::SphereFitter();
	auto err = fb->Fitting(cld, &sphere);

	cout << err*2 << endl;
	cout << sphere.center << endl;
	cout << sphere.r << endl;

	delete fb;
}
