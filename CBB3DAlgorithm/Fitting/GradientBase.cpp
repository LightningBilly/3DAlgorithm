#include <Eigen/Dense>
#include "GradientBase.h"


namespace Fitting {
	double GradientBase::search_alpha(const std::vector<Eigen::Vector3d>& points)
	{
		double alpha = 1.0;
		VK xk= initVK();
		double fk = F_X(points), fn;
		VK gk = G_X(points);
		VK d = -gk;
		double phi = d.dot(gk);
		VK theta, xn, gn;

		auto changeAlpha = [&](double beta) {
			alpha *= beta;
			theta = alpha * d;
			xn = xk + theta;
			transResult(xn);
			fn = F_X(points);
			gn = G_X(points);
		};

		changeAlpha(1);// 初始化

		while (fn > fk + 0.1 * alpha * phi) changeAlpha(0.5);
		while (d.dot(gn) < 0.5 * phi) changeAlpha(2);
		return alpha;
	}
	double GradientBase::Descending(const std::vector<Eigen::Vector3d>& points, void* ele)
	{
		int iterNum = 100;
		double esp = 1e-8;
		double alpha = search_alpha(points);
		VK xk = initVK();
		double fk = F_X(points); // 当前函数值
		VK gk = G_X(points); // 当前梯度
		VK d = -gk; // 最速下降方向
		VK theta = alpha * d; // 下降步长
		VK xn = xk + theta; // 下次到达解
		transResult(xn); //更新解
		double fn = F_X(points); // 与xn对应的函数值
		VK gn = G_X(points);// 下次梯度值

		// 开始使用公式迭代
		while (iterNum--) {
			if (theta.norm() < esp || abs(fk - fn) < esp || gn.norm() < esp) break;

			auto z = gn - gk;
			alpha = theta.dot(z) / z.squaredNorm();
			theta = alpha * d;
			xk = xn;
			xn = xn + theta;
			fk = fn;
			transResult(xn);
			fn = F_X(points);
			gk = gn;
			gn = G_X(points);
			d = -gn;
		}
		Copy(ele);
		return fn;
	}

}

