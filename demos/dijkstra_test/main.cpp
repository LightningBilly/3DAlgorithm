#include<stdio.h>
#include "Dijkstra/Dijkstra.h"
#include<vector>
#include<algorithm>
using namespace std;
// #include "include/PolyMesh/IOManager.h"

// using namespace acamcad::polymesh;

int main() {
	PolyMesh mesh;
	loadMesh("D:/selfad/3DAlgorithm_build/dijkstra/alien.obj", &mesh);
	printf("cnt:%d\n", mesh.numVertices());
	vector<int> p;
	Dijkstra(mesh, 1, 1000, p);

	for (auto n : p) {
		printf("%d\n", n);
	}
	// void Dijkstra(PolyMesh & Mesh, int s_p, int e_p, std::vector<int>&path);
	printf("ok\n");
	return 0;
}