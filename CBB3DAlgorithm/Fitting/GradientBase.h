#ifndef GRADIENTBASE_H_H
#define GRADIENTBASE_H_H

#include <Eigen/Core>
#include <vector>
#include "GeometryTypes.h"


namespace Fitting {
	using VK = Eigen::VectorXd;
	class GradientBase {
	private:
		double search_alpha(const std::vector<Eigen::Vector3d>& points);
	protected:
		/*
		* 设定初始值，获取初向量
		*/
		virtual VK initVK() = 0;

		/*transResult
		* 更新解
		*/
		virtual void transResult(const VK & xk)=0;

		/* F
		* 函数值
		*/
		virtual double F_X(const std::vector<Eigen::Vector3d>& points)=0;

		/*
		* 梯度值
		*/
		virtual Eigen::VectorXd G_X(const std::vector<Eigen::Vector3d>& points)=0;

		/* 获取 结果
		*/
		virtual void Copy(void* ele) = 0;

	public:
		// 梯度下降迭代
		double Descending(const std::vector<Eigen::Vector3d>& points, void* ele);
	};
}

#endif // !FITTINGBASE_H_H
