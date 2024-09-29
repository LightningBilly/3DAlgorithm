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

		changeAlpha(1);// ��ʼ��

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
		double fk = F_X(points); // ��ǰ����ֵ
		VK gk = G_X(points); // ��ǰ�ݶ�
		VK d = -gk; // �����½�����
		VK theta = alpha * d; // �½�����
		VK xn = xk + theta; // �´ε����
		transResult(xn); //���½�
		double fn = F_X(points); // ��xn��Ӧ�ĺ���ֵ
		VK gn = G_X(points);// �´��ݶ�ֵ

		// ��ʼʹ�ù�ʽ����
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

