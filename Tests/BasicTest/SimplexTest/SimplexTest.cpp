#include "SimplexTest.h"
#include "include/Math/Simplex.h"
#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;


void SimplexTest::test1(char *path) {
	cout << "test1" << endl;
	using namespace BasicTools;
	Simplex::LPS lps;

	FILE *fp = fopen(path, "r");
	int n, m;
	int t;
	fscanf(fp, "%d", &t);
	fscanf(fp, "%d%d", &n, &m);
	std::vector<double> ceff(n);
	for(int i=0;i<n;++i)
		fscanf(fp, "%lf", &ceff[i]);
	lps.InitProb(n, ceff, Simplex::OptimizationType(t));

	double b;
	for (int i = 0; i < m; ++i) {
		for(int j=0;j<n;++j)
			fscanf(fp, "%lf", &ceff[j]);
		fscanf(fp, "%lf", &b);
		fscanf(fp, "%d", &t);
		lps.AddCondition(ceff, b, Simplex::CmpType(t));
	}

	fclose(fp);

	auto res = lps.solve();
	printf("是否有解：");
	switch (res.rt)
	{
	case Simplex::NoUpBound:
		puts("NoUpBound");
		return;
	case Simplex::NoSolution:
		puts("NoSolution");
		return;
	case Simplex::More:
		puts("More");
		break;
	case Simplex::OnlyOne:
		puts("OnlyOne");
		break;
	default:
		break;
	}

	printf("Z=%.3f\n", res.Z);
	printf("X取值\n");

	for (int i = 0; i < res.x.size(); ++i)
		printf("x%d: %.3f\n", i, res.x[i]);
}