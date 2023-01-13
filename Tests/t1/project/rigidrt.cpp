#include "rigidrt.h"
#include<stdio.h>
#include<include/Math/MMatrix3.h>
#include<vector>
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

void testRYMatrix() {
	puts("testRYMatrix");
	
	acamcad::RigidRTMatrix rt;
	auto tests = getMVectors();

	for (auto t : tests) {
		auto mat = rt.GetRY(t);
		cout << mat << std::endl;
		cout << t << std::endl;

		cout << "trans: " << (mat * t) << endl;
	}
}