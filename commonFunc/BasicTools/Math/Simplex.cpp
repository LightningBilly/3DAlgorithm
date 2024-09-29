#pragma once

#include "../include/Math/Simplex.h"
#include <iostream>

// #define SIMPLEXDEBUG

using namespace BasicTools;
using namespace Simplex;

int BasicTools::Simplex::CmpDouble(double a)
{
	if (abs(a) < EPS)return 0;
	if (a > 0)return 1;
	return -1;
}

void LPS::InitProb(int n, std::vector<double> &c, OptimizationType ot)
{
	assert(ceff.size() == n);
	varNums = n;
	OT = ot;
	originCeff = c;
	conditionsCeff.clear();
	conditionsB.clear();
	conditionsCmpType.clear();
}

void LPS::AddCondition(std::vector<double> &x, double b, CmpType ct)
{
	assert(x.size() == varNums);
	conditionsCeff.push_back(x);
	conditionsB.push_back(b);
	conditionsCmpType.push_back(ct);
}

Result LPS::solve()
{
	normalize();
	addRelaxVar();
	addManualVar();
	iteration();
	genResult();
	return res;
}

void BasicTools::Simplex::LPS::normalize()
{
	ceff = originCeff;
	// �Ż����ͼ��
	if (OT == MIN)for (auto& c : ceff)c *= -1;
	varType.assign(varNums, Sys);

	// ���������bi�Ƿ񶼴���0
	for (int i = 0; i < conditionsCeff.size(); ++i) {
		if (conditionsB[i] < 0) {
			for (auto& c : conditionsCeff[i])c *= -1;
			conditionsB[i] *= -1;
			if (conditionsCmpType[i] != EQ)conditionsCmpType[i] =CmpType(int(conditionsCmpType[i]) ^1);
		}
	}

}

void BasicTools::Simplex::LPS::addRelaxVar()
{
	// ����map�洢��ʽ
	equaltations.resize(conditionsCmpType.size());
	for (int i = 0; i < equaltations.size(); ++i) 
		for (int j = 0; j < conditionsCeff[i].size(); ++j) equaltations[i][j] = conditionsCeff[i][j];

	for (int i = 0; i < conditionsCmpType.size();++i) {
		auto t = conditionsCmpType[i];
		if (t != EQ) {
			varType.push_back(Relax);
			ceff.push_back(0);
		}

		if (t == GE) {
			equaltations[i][ceff.size() - 1] = -1;
		}
		else if(t==LE)
		{
			equaltations[i][ceff.size() - 1] = 1;
		}
	}
	sysRelaxNumMark = varType.size();
}

double getCeff(std::unordered_map<int, double>& m, int j) {
	if (m.count(j) == 0)return 0;
	return m[j];
}

void BasicTools::Simplex::LPS::addManualVar()
{
	baseVarInd.resize(equaltations.size());
	for (int i = 0; i < equaltations.size(); ++i) {
		// �ȴ��ɳ۱������һ�����
		baseVarInd[i] = -1;
		for (int j = 0; j < sysRelaxNumMark; ++j) {
			// �ж��Ƿ�Ϊ��λ�����ҵ�ǰ��Ϊ1
			if (CmpDouble(getCeff(equaltations[i],j)-1))continue;

			// �ж�������Ϊ0
			bool find = true ;
			for (int k = 0; k < equaltations.size() && find; ++k) {
				if (k == i)continue;
				if (CmpDouble(getCeff(equaltations[k], j))) find = false;
			}

			if (find) {
				baseVarInd[i] = j;
				break;
			}

		}

		// û�ҵ�������˹��������Ż�����ϵ���м����-M
		if (baseVarInd[i] == -1) {
			baseVarInd[i] = varType.size();
			equaltations[i][varType.size()] = 1;
			ceff.push_back(-BIGM);
			varType.push_back(Manual);
		}
	}
}

void BasicTools::Simplex::LPS::iteration()
{	
	std::vector<double> baseCeff(baseVarInd.size()); // CBi
	std::vector<bool> isBaseVar(varType.size(), false);
	for (int i = 0; i < baseVarInd.size(); ++i) {
		baseCeff[i] = ceff[baseVarInd[i]];
		isBaseVar[baseVarInd[i]] = true;
	}
	int n = baseVarInd.size(), m = ceff.size()+1;
	// ��������ʽ
	determinant.resize(baseVarInd.size(), m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m - 1; ++j)
			determinant(i, j) = getCeff(equaltations[i], j);
		determinant(i, m - 1) = conditionsB[i];
	}	

	// �����ε���
	while (1) {
		int inBase = -1, outBase=-1;
		double sigma = 0, theta=0;
		std::vector<double> sigmas(ceff.size(), 0), thetas(n, BIGM);

		// ����sigmaȷ������
		for (int i = 0; i < varType.size(); ++i) {
			// ������������϶���0
			if (isBaseVar[i])continue;

			double t = ceff[i];
			bool unbound = true;
			for (int j = 0; j < n; ++j) {
				t -= baseCeff[j] * determinant(j, i);
				if (unbound && determinant(j, i) > 0)unbound = false;
			}
			sigmas[i] = t;
			if (unbound && t > 0) {
				std::cout << "NoUpBound" << std::endl;
				res.rt = NoUpBound;
#ifdef SIMPLEXDEBUG
				printFram(sigmas, thetas);
#endif
				return;
			}
			if (sigma < t) {
				inBase = i;
				sigma = t;
			}
			if (CmpDouble(t) == 0 && inBase == -1) {
				inBase = -2;
			}
		}

		// �������������ж��Ƿ��޽⣬�鿴�������Ƿ����˹�����		
		for (int i = 0; i < baseVarInd.size() && inBase<0;++i) {
			if (varType[baseVarInd[i]] == Manual) {
				res.rt = NoSolution;
				std::cout << "NoSolution" << std::endl;
#ifdef SIMPLEXDEBUG
				printFram(sigmas, thetas);
#endif
				return;
			}
		}

		// �н�, ����
		if (inBase == -1) {
			res.rt = OnlyOne;
#ifdef SIMPLEXDEBUG
			printFram(sigmas, thetas);
#endif
			return;
		}
		if(inBase==-2)
		{
			res.rt = More;
#ifdef SIMPLEXDEBUG
			printFram(sigmas, thetas);
#endif
			return;
		}

		// ��û�������������˻�
		for (int i = 0; i < equaltations.size(); ++i) {
			if(CmpDouble(determinant(i, inBase))<=0)continue;
			auto t = determinant(i, m - 1) / determinant(i, inBase);
			thetas[i] = t;
			if (outBase == -1 || t < theta) {
				theta = t;
				outBase = i;
			}
		}

#ifdef SIMPLEXDEBUG
		printFram(sigmas, thetas);
#endif
		//����
		isBaseVar[baseVarInd[outBase]] = false;
		baseVarInd[outBase] = inBase;
		baseCeff[outBase] = ceff[inBase];
		isBaseVar[inBase] = true;

		// �任����ʽ
		double v = determinant(outBase, inBase);
		for (int j = 0; j < m; ++j)determinant(outBase, j) /= v;

		for (int i = 0; i < n; ++i) {
			if (i == outBase)continue;
			v= determinant(i, inBase);
			for (int j = 0; j < m; ++j)determinant(i, j) -= determinant(outBase,j)*v;
		}
	}
}

void BasicTools::Simplex::LPS::genResult()
{
	if (res.rt == NoUpBound || res.rt == NoSolution)return;
	res.Z = 0;
	res.x.assign(varNums, 0);
	for (int i = 0; i < baseVarInd.size(); ++i) {
		res.Z += ceff[baseVarInd[i]] * determinant(i, varType.size());
		if(baseVarInd[i]<varNums)res.x[baseVarInd[i]] = determinant(i, varType.size());
	}
	if (OT == MIN)res.Z *= -1;	

#ifdef SIMPLEXDEBUG
	printf("������ͣ�%s\n", OT == MIN ? "MIN" : "MAX");
	/*printf("�Ƿ��н⣺");
	switch (res.rt)
	{
	case NoUpBound:
		puts("NoUpBound");
		return;
	case NoSolution:
		puts("NoSolution");
		return;
	case More:
		puts("More");
		break;
	case OnlyOne:
		puts("OnlyOne");
		break;
	default:
		break;
	}

	printf("Z=%.3f\n", res.Z);
	printf("Xȡֵ\n");

	for (int i = 0; i < res.x.size(); ++i) 
		printf("x%d: %.3f\n", i, res.x[i]);*/
#endif
}

void BasicTools::Simplex::LPS::printFram(const std::vector<double>& sigma, const std::vector<double>& theta)
{
	double z = 0;
	//	��һ��
	printf("\tCj\t");
	for (int i = 0; i < ceff.size(); ++i) {
		if (CmpDouble(BIGM + ceff[i]) == 0) {
			printf("-M\t");
		}
		else {
			printf("%.3f\t", ceff[i]);
		}
	}
	puts("");
	//	�ڶ���
	printf("CBi\ti\t");
	for (int i = 0; i < ceff.size(); ++i) {
		printf("x%d\t", i);
	}
	printf("bi\tthi\t");
	puts("");
	// ��ӡ����
	int m = ceff.size() + 1;
	for (int i = 0; i < baseVarInd.size(); ++i) {
		if (CmpDouble(BIGM + ceff[baseVarInd[i]])==0) printf("-M");
		else printf("%.2f", ceff[baseVarInd[i]]);
		printf("\t%d\t", baseVarInd[i]);

		for (int j = 0; j < m; ++j) {
			printf("%.3f\t", determinant(i, j));
		}
		z += determinant(i, m - 1)* ceff[baseVarInd[i]];
		if (CmpDouble(BIGM - theta[i]))printf("%.2f\t", theta[i]);
		else printf("-\t");
		puts("");
	}

	// ������
	printf("\tej\t");
	for (int i = 0; i < ceff.size(); ++i) {
		printf("%.2e\t", sigma[i]);
		//std::cout << std::scientific << std::precision(2) << sigma[i];
	}

	printf("Z=%.3e\t", z);
	puts("");
	puts("----------------------------------------------------------------------------------------");

}