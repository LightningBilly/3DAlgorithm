#include "gauss.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include <Fitting/gauss/FittingLinePCA.h>
#include<include/IOType/PointCloud.h>
#include<Fitting/TestCaseGen.h>
#include<Fitting/gauss/TestAllCase.h>
#include<Fitting/gauss/FittingLine.h>
#include<Fitting/gauss/FittingPlanePCA.h>
#include<Fitting/gauss/FittingPlane.h>
#include<Fitting/gauss/FittingCircle2D.h>
#include<Fitting/gauss/SphereFitter.h>
#include<Fitting/gauss/CircleFitter.h>
#include<Fitting/gauss/CylinderFitter.h>
#include<Fitting/gauss/ConeFitter.h>
#include< cmath>
using namespace std;

void FittingLinePCATest() {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/commonFunc/BasicTools/include/IOType/point.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		cout << "ps: " << endl;
		cout << p << endl;
	}
	printf("ok\n");

	Fitting::Line line;
	auto err = FittingPCA(cld, line);

	cout << err << endl;
	cout << line.BasePoint << endl;
	cout << line.Orient << endl;
}


void FittingPlanePCATest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;

	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/commonFunc/BasicTools/include/IOType/point.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		cout << "ps: " << endl;
		cout << p << endl;
	}
	printf("ok\n");

	Fitting::Plane plane;
	auto err = FittingPCA(cld, plane);

	cout << err << endl;
	cout << plane.BasePoint << endl;
	cout << plane.Orient << endl;
}

//  ./FittingRun.exe  FittingLineTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b01.asc"
void FittingLineTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	//cout << PointCloud::readPoint(argv[2], cld) << endl;
	cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/CBB3DAlgorithm/Fitting/gauss/data/b01.asc", cld) << endl;
	cout.precision(20);
	for (auto& p : cld) {
		cout << "ps: " << endl;
		cout << p << endl;
	}
	printf("ok\n");

	Fitting::Line line;
	Fitting::FittingBase* fb = new Gauss::FittingLine();
	auto err = fb->Fitting(cld, &line);

	cout << err << endl;
	cout << line.BasePoint << endl;
	cout << line.Orient << endl;

	delete fb;
}


//  ./FittingRun.exe  FittingPlaneTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b05.asc"
void FittingPlaneTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:/selfad/alg_and_graph/3DAlgorithm/CBB3DAlgorithm/Fitting/gauss/data/b01.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Plane plane;
	Fitting::FittingBase* fb = new Gauss::FittingPlane();
	auto err = fb->Fitting(cld, &plane);

	cout << err << endl;
	cout << plane.BasePoint << endl;
	cout << plane.Orient << endl;

	delete fb;
}


//  ./FittingRun.exe  FittingSphereTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b38.asc"
void FittingSphereTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Sphere sphere;
	Fitting::FittingBase* fb = new Gauss::SphereFitter();
	auto err = fb->Fitting(cld, &sphere);

	cout << err << endl;
	cout << sphere.center << endl;
	cout << sphere.r << endl;

	delete fb;
}


//  ./FittingRun.exe  FittingCircleTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b09.asc"
void FittingCircleTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Circle circle;
	Fitting::FittingBase* fb = new Gauss::CircleFitter();
	auto err = fb->Fitting(cld, &circle);

	cout << err << endl;
	cout << circle.center << endl;
	cout << circle.orient << endl;
	cout << circle.r << endl;

	delete fb;
}



//  ./FittingRun.exe  FittingCylinderTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc"
void FittingCylinderTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Cylinder cylinder;
	Fitting::FittingBase* fb = new Gauss::CylinderFitter();
	auto err = fb->Fitting(cld, &cylinder);

	cout << err << endl;
	cout << cylinder.center << endl;
	cout << cylinder.orient << endl;
	cout << cylinder.r << endl;

	delete fb;
}

//  ./FittingRun.exe  FittingConeTest  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b26.asc"
void FittingConeTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;
	cout << PointCloud::readPoint(argv[2], cld) << endl;
	//cout << PointCloud::readPoint("D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\b16.asc", cld) << endl;
	cout.precision(20);
	printf("ok\n");

	Fitting::Cone cone;
	Fitting::FittingBase* fb = new Gauss::ConeFitter();
	auto err = fb->Fitting(cld, &cone);

	cout << err << endl;
	cout << cone.center << endl;
	cout << cone.orient << endl;
	cout << cone.r << endl;
	cout << cone.alpha / M_PI * 180 << endl;

	delete fb;
}


void xmlCaseGen(int argc, char** argv) {
	string xmlPath = argv[2];
	string outPath = argv[3];
	string package = argv[4];

	cout << Fitting::Xml2Txt(xmlPath, outPath, package) << endl;
}


void xmlAnsGen(int argc, char** argv) {
	string xmlPath = argv[2];
	string outPath = argv[3];
	string package = argv[4];

	cout << Fitting::Xml2Ans(xmlPath, outPath, package) << endl;
}

void guassTestAll(int argc, char** argv) {
	Gauss::TestAllCase();
}


void FittingCircle2DTest(int argc, char** argv) {
	using namespace Gauss;
	std::vector<Eigen::Vector3d> cld;

	cout << PointCloud::readPoint(argv[2], cld) << endl;
	cout.precision(20);


	Fitting::Circle2D circle;
	Fitting::FittingBase* fb = new Gauss::FittingCircle2D();
	auto err = fb->Fitting(cld, &circle);
	delete fb;

	cout << err << endl;
	cout << circle.center << endl;
	cout << circle.r << endl;

}