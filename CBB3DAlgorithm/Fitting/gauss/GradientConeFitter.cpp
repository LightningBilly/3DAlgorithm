#include "GradientConeFitter.h"

/*
 梯度下降法相关代码
 拟合 (x-x0)^2+(y-y0)^2=(r-kz)^2
*/
namespace Gauss {
	// 获取函数值f(X)
	double GradientConeFitter::F_X(const std::vector<Eigen::Vector3d>& points) {
		double f = 0;
		double k = tan(cone.alpha / 2);
		for (auto& p : points) {
			Eigen::Vector3d q(p.x() - cone.center.x(), p.y() - cone.center.y(), cone.r - k * p.z());
			double d = q.squaredNorm() - 2 * q.z() * q.z();
			f += d*d;
		}
		return f;
	}

	// 获取梯度值f'(X)
	Fitting::VK GradientConeFitter::G_X(const std::vector<Eigen::Vector3d>& points) {
		Fitting::VK g(3);
		g.setZero();
		double k = tan(cone.alpha/2);
		for (auto& p : points) {
			Eigen::Vector3d q(Eigen::Vector3d(p.x() - cone.center.x(), p.y() - cone.center.y(), cone.r - k * p.z()));
			double c = q.squaredNorm()-2*q.z()*q.z();
			for (int i = 0; i < 3; ++i)g(i) += c * q(i);
		}
		g *= -4;
		return g;
	}

	Fitting::VK GradientConeFitter::initVK()
	{
		cone = copyCone;
		Fitting::VK xk(3);
		xk << cone.center.x(), cone.center.y(), cone.r;
		return xk;
	}

	void GradientConeFitter::transResult(const Fitting::VK& xk) {
		cone.center = xk;
		cone.center.z() = 0;
		cone.r = xk.z();
	}

	void GradientConeFitter::Copy(void* ele)
	{
		memcpy(ele, &cone, sizeof(Fitting::Cone));
	}

	GradientConeFitter::GradientConeFitter(const Fitting::Cone& c)
	{
		cone = c;
		copyCone = c;
	}
}
