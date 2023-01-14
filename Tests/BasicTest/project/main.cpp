#include<stdio.h>
#include "rigidrt.h"
#include<cmath>
#include<climits>

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
	printf("%f\n", sin(270.0 / 180 * pi));
	printf("%f\n", sin(double(270 - 360) / 180 * pi));
	printf("%f\n", sin(888.89 / 180 * pi));
	printf("%f\n", sin(double(888.89 - 360) / 180 * pi));
	// testRYMatrix();
	// testRXMatrix();
	// testAngleMod();
	testXRotate();
	return 0;
}