#include<stdio.h>
#include "rigidrt.h"

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
	
	testRYMatrix();
	return 0;
}