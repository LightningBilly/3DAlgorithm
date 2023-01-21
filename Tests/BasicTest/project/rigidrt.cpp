#include "rigidrt.h"
#include<stdio.h>
#include<include/Math/MMatrix3.h>
#include<vector>
#include<windows.h>
#include<iostream>
using namespace std;

vector<acamcad::Point> getMVectors() {
	vector<acamcad::Point> v;
	for (double i = 0; i < 100; ++i) {
		v.push_back({ 0,1,i });
		v.push_back({ 0,i,1 });
		v.push_back({ 0,1,-i });
		v.push_back({ 0,i,-1 });
		v.push_back({ 0,-1,i });
		v.push_back({ 0,-i,1 });
		v.push_back({ 0,-1,-i });
		v.push_back({ 0,-i,-1 });
	}

	return v;
}


vector<acamcad::Point> getMVectorsZOX() {
	vector<acamcad::Point> v;
	for (double i = 0; i < 100; ++i) {
		v.push_back({ 1,0,i });
		v.push_back({ i,0,1 });
		v.push_back({ 1,0,-i });
		v.push_back({ i,0,-1 });
		v.push_back({ -1,0,i });
		v.push_back({ -i,0,1 });
		v.push_back({ -1,0,-i });
		v.push_back({-i,0,-1 });
	}

	return v;
}

vector<double> getAngles() {
	vector<double> v;
	for (double i = 0; i < 1000; i+=0.1) {
		v.push_back(i);
		v.push_back(-i);
	}

	return v;
}

void testRYMatrix() {
	puts("testRYMatrix");
	
	acamcad::RigidRTMatrix rt;
	auto tests = getMVectors();

	for (auto &t : tests) {
		auto mat = rt.GetRY(t);
		cout << mat << std::endl;
		cout << t << std::endl;

		cout << "trans: " << (mat * t) << endl;
	}
}


void testRXMatrix() {
	puts("testRXMatrix");

	acamcad::RigidRTMatrix rt;
	auto tests = getMVectorsZOX();

	for (auto& t : tests) {
		auto mat = rt.GetRX(t);
		cout << mat << std::endl;
		cout << t << std::endl;

		cout << "trans: " << (mat * t) << endl;
	}
}

void testXRotate() {
	puts("testXRotate");

	acamcad::RigidRTMatrix rt;
	double start = 46;
	for (double theta = -start; theta < start; theta += 0.1) {
		auto mt = rt.GetXRotate(theta);
		auto Z = acamcad::Point(0,0,1);
		auto rotateZ = mt * Z;

		cout << "-------" << endl;
		cout << "theta : " << theta << endl;
		cout << "rotateZ : " << rotateZ << endl;
	
	}
}

void testAngleMod() {
	puts("testAngleMod");
	acamcad::RigidRTMatrix rt;
	for (auto t : getAngles()) {
		Sleep(100);
		cout << "---" << endl;
		cout << t << endl;
		cout << rt.angleMod(t) << endl;
	}
}

void testRotate() {
	puts("testRotate");
	vector<vector<double>> tests = {
		// 沿Z轴转45度
		{0,0,0, 0,0,1, 45, 1,0,1},
		// 沿Z轴转－45度
		{0,0,0, 0,0,1, -45, 1,0,1},
		// 沿Y轴转45度
		{0,0,0, 0,1,0, 45, 1,0,1},
		// 沿Y轴转-45度
		{0,0,0, 0,1,0, -45, 1,0,1},
		// 沿Y轴转0度
		{0,0,0, 0,1,0, 0, 1,0,1},
		// 沿Y轴转90度
		{0,0,0, 0,1,0, 90, 1,0,1},
		// 沿Y轴转180度
		{0,0,0, 0,1,0, 180, 1,0,1},
		// 沿Y轴转220度
		{0,0,0, 0,1,0, 220, 1,0,1},
		// 沿Y轴转360度
		{0,0,0, 0,1,0, 360, 1,0,1},
		// 沿Y轴转361度
		{0,0,0, 0,1,0, 361, 1,0,1},

		// 沿-Y轴转45度
		{0,0,0, 0,-1,0, 45, 1,0,1},
		// 沿-Y轴转-45度
		{0,0,0, 0,-1,0, -45, 1,0,1},
		// 沿-Y轴转0度
		{0,0,0, 0,-1,0, 0, 1,0,1},
		// 沿-Y轴转90度
		{0,0,0, 0,-1,0, 90, 1,0,1},
		// 沿-Y轴转180度
		{0,0,0, 0,-1,0, 180, 1,0,1},
		// 沿-Y轴转220度
		{0,0,0, 0,-1,0, 220, 1,0,1},
		// 沿-Y轴转360度
		{0,0,0, 0,-1,0, 360, 1,0,1},
		// 沿-Y轴转361度
		{0,0,0, 0,-1,0, 361, 1,0,1},


		// 沿1,1,1轴转90度
		{0,0,0, 1,1,1, 90, 1,0,1},
		{0,0,0, 1,1,1, -90, 1.24402, 0.666667,0.0893164},


		{0,0,0, 1,2,3, 90, 1,0,1},
		{1,1,1, 2,3,4, 90, 2,1,2},
		
	};
	for (auto& t : tests) {
		cout << "----" << endl;
		acamcad::RigidRTMatrix rt(Eigen::Vector3d(t[0], t[1], t[2]), Eigen::Vector3d(t[3], t[4], t[5]), t[6]);
		//acamcad::RigidRTMatrix rt(Eigen::Vector3d(0,0,0), 45.0f);
		acamcad::Point p(t[7], t[8], t[9]);
		acamcad::Point p1 = rt.Trans(p);
		cout << "p1: " << p1 << endl;
	}
	
}


void testMulti() {
	puts("testRotate");
	vector<vector<double>> tests = {
		{1,0,0, 1,1,0, 180, 2,0,0},
		{-1,0,0, -1,1,0, 180, 1.24402, 0.666667,0.0893164},


		{1,0,0, 1,2,5, 55, 2,3,4},
		{10,0,0, 3,-5,-6, 88, 1.24402, 0.666667,0.0893164},
		
	};
	for (int i = 0; i < tests.size();i+=2) {
		cout << "----" << endl;
		auto& t = tests[i];
		auto& t2 = tests[i + 1];
		acamcad::RigidRTMatrix rt1(Eigen::Vector3d(t[0], t[1], t[2]), Eigen::Vector3d(t[3], t[4], t[5]), t[6]);
		acamcad::Point p(t[7], t[8], t[9]);
		acamcad::Point p1 = rt1.Trans(p);
		cout << "p1: " << p1 << endl;

		acamcad::RigidRTMatrix rt2(Eigen::Vector3d(t2[0], t2[1], t2[2]), Eigen::Vector3d(t2[3], t2[4], t2[5]), t2[6]);
		acamcad::Point p2 = rt2.Trans(p1);
		cout << "p2: " << p2 << endl;

		cout << "multi app ----- " << endl;

		auto rtmulti = rt2 * rt1;
		acamcad::Point p3 = rtmulti.Trans(p);
		cout << "p3: " << p3 << endl;

	}	


	
}