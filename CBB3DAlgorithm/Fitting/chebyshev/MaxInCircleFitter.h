#ifndef FITTIINGMAXCIRCLEIN_H_H
#define FITTIINGMAXCIRCLEIN_H_H
#include "../FittingBase.h"

namespace Chebyshev {
	double F(Fitting::Circle2D circle, const Point &p);
	double GetError(Fitting::Circle2D circle, const std::vector<Eigen::Vector3d>& points);
	class MaxInCircleFitter : public Fitting::FittingBase  {
		Fitting::Circle2D circle;
		Fitting::Matrix Jacobi(const std::vector<Eigen::Vector3d>& points);

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
	public:
		MaxInCircleFitter();
	};
}


#endif // !FITTIINGMAXCIRCLEIN_H_H
