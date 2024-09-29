#ifndef GRADIENTCONE_H_H
#define GRADIENTCONE_H_H
#include "../FittingBase.h"
#include "../GradientBase.h"

namespace Gauss {
	class GradientConeFitter: public Fitting::GradientBase  {
		Fitting::Cone cone, copyCone;

		/*
		* 设定初始值，获取初向量
		*/
		Fitting::VK initVK();

		/*transResult
		* 更新解
		*/
		void transResult(const Fitting::VK& xk);

		/* F
		* 函数值
		*/
		double F_X(const std::vector<Eigen::Vector3d>& points);

		/*
		* 梯度值
		*/
		Eigen::VectorXd G_X(const std::vector<Eigen::Vector3d>& points);

		/* 获取 结果
		*/
		void Copy(void* ele);

	public:
		GradientConeFitter(const Fitting::Cone &c);
	};
}


#endif // !GRADIENTCONE_H_H
