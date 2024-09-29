#pragma once

#include "Eigen/Core"
#include <vector>
#include <unordered_map>

namespace BasicTools
{
	namespace Simplex {
		static double BIGM = 1e100;
		static double EPS = 1e-15;
		int CmpDouble(double a);

		enum ResultType { OnlyOne, More, NoUpBound, NoSolution }; // Ψһ�⣬�����⣬�޽�⣬�޿��н�
		enum VarType { Sys, Relax, Manual }; // ��������

		struct Result {
			ResultType rt;
			double Z;
			std::vector<double> x;
		};

		enum OptimizationType{MAX, MIN}; // �Ż����ͣ���������С
		enum CmpType { GE, LE, EQ }; // �Ƚϳƺţ����ڣ����ڵ��ڣ�С�ڵ���

		class LPS
		{
		public:
			/*
			* ��ʼ��
			* �趨����������Ŀ�꺯��ϵ�����Ż�����
			*/
			void InitProb(int n, std::vector<double> &c, OptimizationType ot);
			/*
			* �������
			* ����xǰ����xϵ��, b�����ұ߳�����ct�������
			*/
			void AddCondition(std::vector<double> &x, double b, CmpType ct);

			/*
			* ���滮
			*/
			Result solve();

		private:
			OptimizationType OT;
			int varNums; 
			std::vector<double> originCeff;
			std::vector<std::vector<double>> conditionsCeff;
			std::vector<double> conditionsB;
			std::vector<CmpType> conditionsCmpType;


		private:
			// ������̱���
			std::vector<double> ceff; // ��׼�����ϵ��
			std::vector<std::unordered_map<int , double>> equaltations;// ��ʽ
			std::vector<VarType> varType;
			int sysRelaxNumMark;// �ɳ۱���+ԭʼ��������
			Result res;
			Eigen::Matrix<double, -1, -1> determinant; // ����ʽ
			std::vector<int> baseVarInd; // ���������

			/*
			* ��׼��
			*/
			void normalize();

			/*
			* ����ɳ۱����������ʽ
			*/
			void addRelaxVar();

			/*
			* ����˹�����, ��ó�ʼ��
			*/
			void addManualVar();

			/*
			* ����
			*/
			void iteration();

			/*
			* ���ܽ��
			*/
			void genResult();


			/*
			* �м����
			*/
			void printFram(const std::vector<double>& sigma, const std::vector<double>& theta);
		};

	}
}

