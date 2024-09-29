#include<stdio.h>
#include "rigidrt.h"
#include<cmath>
#include<climits>
#include<tests/GeometryTest.h>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include<iostream>

using namespace std;

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
	//printf("%d\n", BasicToolsTest::PointProjectPlane_Test());
	// testRYMatrix();
	// testRXMatrix();
	// testAngleMod();
	// testXRotate();
	// testRotate();
	// testMulti();

	using MyMesh = OpenMesh::TriMesh_ArrayKernelT<>;
	MyMesh mesh;
	MyMesh::VertexHandle vhandle[4];
	MyMesh::FaceHandle   fhandle;
	// 添加4个点
	vhandle[0] = mesh.add_vertex(MyMesh::Point(-1, -1, 1));
	vhandle[1] = mesh.add_vertex(MyMesh::Point(1, -1, 1));
	vhandle[2] = mesh.add_vertex(MyMesh::Point(1, 1, 1));
	vhandle[3] = mesh.add_vertex(MyMesh::Point(-1, 1, 1));

	// 添加4边形，会被自动分成2个三角形
	std::vector<MyMesh::VertexHandle>  face_vhandles;
	face_vhandles.push_back(vhandle[0]);
	face_vhandles.push_back(vhandle[1]);
	face_vhandles.push_back(vhandle[2]);
	face_vhandles.push_back(vhandle[3]);
	fhandle = mesh.add_face(face_vhandles);
	OpenMesh::IO::write_mesh<MyMesh>(mesh, "D:/abc.obj");
	cout<< mesh.n_vertices()<<endl;
	cout << mesh.n_faces() << endl;
	return 0;
}