#include<stdio.h>
#include <include/PolyMesh/IOManager.h>
#include <include/VTK/vtk.h>
#include <include/Math/MPoint3.h>
using namespace acamcad::polymesh;
int main() {

	printf("ok\n");
	PolyMesh mesh;
	loadMesh("D:/selfad/3DAlgorithm_build/t1/project/Release/alien.obj", &mesh);
	printf("%d\n", mesh.numVertices());

	acamcad::VTK vtk;

	// vtk.add_line(acamcad::MPoint3(), acamcad::MPoint3(1,1,1));
	vtk.read_lines("D:/lines.vtk");
	vtk.show_lines();
	printf("num: %d\n", vtk.lines.size());
	return 0;
}