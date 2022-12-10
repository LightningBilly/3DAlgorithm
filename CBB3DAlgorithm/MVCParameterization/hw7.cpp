//
// Created by chenbinbin on 2022/3/22.
//

// arap_deformation
#include "hw7.h"
#include <fstream>
#include"include/PolyMesh/IOManager.h"
#include"include/PolyMesh/PolyMesh.h"
#include <Eigen/Sparse>
#define pi 3.1415926
using namespace acamcad;
using namespace polymesh;
using namespace std;
using namespace Eigen;

PolyMesh mesh;

void MVCCoordinates(PolyMesh* mesh)
{
	int v_n = mesh->numVertices();
	int iter;
	int boundary_num=0;

	VectorXd u(v_n), v(v_n);// u, v代表方程行列式的B列

	for (VertexIter v_it = mesh->vertices_begin(); v_it != mesh->vertices_end(); ++v_it)
	{
		if (mesh->isBoundary(*v_it))boundary_num++;
	}

	MHalfedge* first_heh= *mesh->halfedge_begin();
	// 查找边界
	for (HalfEdgeIter he_it = mesh->halfedge_begin(); he_it != mesh->halfedge_end(); ++he_it)
	{
		if (mesh->isBoundary(*he_it))
		{
			first_heh = *he_it;
			break;
		}
	}
	MHalfedge* iter_heh = first_heh->next();
	iter = 0;
	// 初始化边界点的uv值
	while (iter_heh != first_heh)
	{
		MVert* from_v = iter_heh->fromVertex();
		u[from_v->index()] = cos(double(2 * pi * iter / boundary_num));
		v[from_v->index()] = sin(double(2 * pi * iter / boundary_num));
		iter_heh = iter_heh->next();
		iter++;
	}
	u[first_heh->fromVertex()->index()] = cos(double(2 * pi * iter / boundary_num));
	v[first_heh->fromVertex()->index()] = sin(double(2 * pi * iter / boundary_num));

	SparseMatrix<double> weight(v_n, v_n);
	std::vector<Triplet<double>> triplet;

	// 针对每个面计算出边的wij. 后面可以聚合到矩阵中。
	for (FaceIter f_it = mesh->polyfaces_begin(); f_it != mesh->polyfaces_end(); ++f_it)
	{
		MHalfedge* heh = (*f_it)->halfEdge();
		MVert* v0 = heh->fromVertex();
		MVert* v1 = heh->toVertex();
		MHalfedge* next_heh = heh->next();
		MVert* v2 = next_heh->toVertex();

		double l2 = (v0->position() - v1->position()).norm();
		double l1 = (v0->position() - v2->position()).norm();
		double l0 = (v1->position() - v2->position()).norm();

		double angle = acos(dot(v2->position() - v0->position(), v1->position() - v0->position()) / (l1 * l2));
		triplet.push_back(Triplet<double>(v0->index(), v1->index(), tan(angle * 0.5) / l2));
		triplet.push_back(Triplet<double>(v0->index(), v2->index(), tan(angle * 0.5) / l1));

		angle = acos(dot(v0->position() - v1->position(), v2->position() - v1->position()) / (l2 * l0));
		triplet.push_back(Triplet<double>(v1->index(), v0->index(), tan(angle * 0.5) / l2));
		triplet.push_back(Triplet<double>(v1->index(), v2->index(), tan(angle * 0.5) / l0));

		angle = acos(dot(v0->position() - v2->position(), v1->position() - v2->position()) / (l0 * l1));
		triplet.push_back(Triplet<double>(v2->index(), v0->index(), tan(angle * 0.5) / l1));
		triplet.push_back(Triplet<double>(v2->index(), v1->index(), tan(angle * 0.5) / l0));
	}
	// 矩阵聚合
	weight.setFromTriplets(triplet.begin(), triplet.end());

	SparseMatrix<double> matrix(v_n, v_n);

	triplet.clear();
	for (VertexIter v_it = mesh->vertices_begin(); v_it != mesh->vertices_end(); ++v_it)
	{
		// 边界处只要设置 matirx[i][i]=1
		if (mesh->isBoundary(*v_it)) {
			triplet.push_back(Triplet<double>((*v_it)->index(), (*v_it)->index(), 1));
			continue;
		}

		// 内部点，设置 B列为0
		u[(*v_it)->index()] = 0;
		v[(*v_it)->index()] = 0;

		// maxtrix[i][i] = sum(wij), maxtrix[i][j] = -wij 
		for (VertexVertexIter vv_it = mesh->vv_iter(*v_it); vv_it.isValid(); ++vv_it)
		{
			triplet.push_back(Triplet<double>((*v_it)->index(), (*vv_it)->index(), -weight.coeff((*v_it)->index(), (*vv_it)->index())));
			triplet.push_back(Triplet<double>((*v_it)->index(), (*v_it)->index(), weight.coeff((*v_it)->index(), (*vv_it)->index())));
		}
	}
	matrix.setFromTriplets(triplet.begin(), triplet.end());
	SparseLU<SparseMatrix<double>> solver;
	solver.analyzePattern(matrix);
	solver.factorize(matrix);
	VectorXd result_u = solver.solve(u);
	VectorXd result_v = solver.solve(v);

	for (VertexIter v_it = mesh->vertices_begin(); v_it != mesh->vertices_end(); ++v_it)
	{
		(*v_it)->setPosition(result_u[(*v_it)->index()], result_v[(*v_it)->index()], 0);
	}
}


void mvc_parameterization()
{
	cout << "mvc_parameterization" << endl;
    // 源文件路径
    string mesh_path = string(FILE_ROOT) +"/src";
    // mesh_path += "/Bunny_head.obj";
    mesh_path += "/human.obj";
    loadMesh(mesh_path, &mesh);
    cout << FILE_A << endl;
    cout << mesh_path << endl;
	MVCCoordinates(&mesh);
	string out_mesh_path = string(FILE_ROOT) + "/src";
	out_mesh_path += "/result_human.obj";
    writeMesh(out_mesh_path, &mesh);
}