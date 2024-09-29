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

		enum ResultType { OnlyOne, More, NoUpBound, NoSolution }; // 唯一解，无穷多解，无界解，无可行解
		enum VarType { Sys, Relax, Manual }; // 变量类型

		struct Result {
			ResultType rt;
			double Z;
			std::vector<double> x;
		};

		enum OptimizationType{MAX, MIN}; // 优化类型，求最大或最小
		enum CmpType { GE, LE, EQ }; // 比较称号，等于，大于等于，小于等于

		class LPS
		{
		public:
			/*
			* 初始化
			* 设定变量个数，目标函数系数，优化类型
			*/
			void InitProb(int n, std::vector<double> &c, OptimizationType ot);
			/*
			* 添加条件
			* 向量x前面是x系数, b代表右边常数，ct代表符号
			*/
			void AddCondition(std::vector<double> &x, double b, CmpType ct);

			/*
			* 求解规划
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
			// 运算过程变量
			std::vector<double> ceff; // 标准化后的系数
			std::vector<std::unordered_map<int , double>> equaltations;// 等式
			std::vector<VarType> varType;
			int sysRelaxNumMark;// 松驰变量+原始变量个数
			Result res;
			Eigen::Matrix<double, -1, -1> determinant; // 行列式
			std::vector<int> baseVarInd; // 基变量编号

			/*
			* 标准化
			*/
			void normalize();

			/*
			* 添加松驰变量，构造等式
			*/
			void addRelaxVar();

			/*
			* 添加人工变量, 获得初始基
			*/
			void addManualVar();

			/*
			* 迭代
			*/
			void iteration();

			/*
			* 汇总结果
			*/
			void genResult();


			/*
			* 中间过程
			*/
			void printFram(const std::vector<double>& sigma, const std::vector<double>& theta);
		};

	}
}

