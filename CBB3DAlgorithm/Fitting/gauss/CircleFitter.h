#ifndef FITTIINGCIRCLE_H_H
#define FITTIINGCIRCLE_H_H
#include "../FittingBase.h"

namespace Gauss {
	double F(Fitting::Circle circle, const Point &p);
	double GetError(Fitting::Circle circle, const std::vector<Eigen::Vector3d>& points);
	class CircleFitter: public Fitting::FittingBase  {
		Fitting::Circle circle;
		Fitting::Matrix Jacobi(const std::vector<Eigen::Vector3d>& points);

		/* beforHook
		* 每次迭代前的准备工作
		*/
		void beforHook(const std::vector<Eigen::Vector3d>& points);

		/* afterHook
		* 迭代后更新答案
		*/
		void afterHook(const Eigen::VectorXd& xp);


		/* 获取 d数组
		*/
		Eigen::VectorXd getDArray(const std::vector<Eigen::Vector3d>& points);

		// GetInitFit
		bool GetInitFit(const std::vector<Eigen::Vector3d>& points);
		
		/* F
		* 距离函数
		*/
		double F(const Eigen::Vector3d& p);

		/* 获取 最小二乘残差
		*/
		double  GetError(const std::vector<Eigen::Vector3d>& points);

		/* 获取 结果
		*/
		void Copy(void* ele);
	};
}


#endif // !FITTIINGCIRCLE_H_H
