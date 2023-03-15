#include<stdio.h>
#include "rigidrt.h"
#include<cmath>
#include<climits>
#include<tests/GeometryTest.h>

void checkType(int a) {
	puts("int");
}


void checkType(double a) {
	puts("double");
}

void checkType(float a) {
	puts("float");
}

template<typename T>
class M{
public:
	T v;
	
	T& operator()(int a, int b) {
		printf("%d %d\n", a,b);

		return v;
	}
};

#define MT(type, typesuffix) using M##typesuffix=M<type>;

MT(int, i)
MT(double, d)
MT(float, f)

int main() {

	const double pi = acos(-1);
	printf("%d\n", BasicToolsTest::PointProjectPlane_Test());
	// testRYMatrix();
	// testRXMatrix();
	// testAngleMod();
	// testXRotate();
	// testRotate();
	// testMulti();
	return 0;
}