#include<stdio.h>
#include "SimplexTest.h"
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

int main(int argc, char ** argv) {
	// printf("%d %d %d %d %d %d %d %d %d %d", ' ', '\n', '\r', '\t', '/', '<', '>', '=', '?', '!');
	if (argc < 2) {
		puts("path"); return -1;
	}
	SimplexTest::test1(argv[1]);
	return 0;
}