#include "rigidrt.h"
#include<stdio.h>
#include<include/Math/MMatrix3.h>
#include<vector>
#include<windows.h>
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