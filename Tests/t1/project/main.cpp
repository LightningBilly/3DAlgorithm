#include<stdio.h>
#include <IOManager.h>
using namespace acamcad::polymesh;
int main() {

	printf("ok\n");
	PolyMesh mesh;
	loadMesh("D:/selfad/3DAlgorithm_build/t1/project/Release/alien.obj", &mesh);
	printf("%d\n", mesh.numVertices());
	return 0;
}