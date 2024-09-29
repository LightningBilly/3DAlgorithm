#ifndef GRADIENTCONE_H_H
#define GRADIENTCONE_H_H
#include "../FittingBase.h"
#include "../GradientBase.h"

namespace Gauss {
	class GradientConeFitter: public Fitting::GradientBase  {
		Fitting::Cone cone, copyCone;

		/*
		* �趨��ʼֵ����ȡ������
		*/
		Fitting::VK initVK();

		/*transResult
		* ���½�
		*/
		void transResult(const Fitting::VK& xk);

		/* F
		* ����ֵ
		*/
		double F_X(const std::vector<Eigen::Vector3d>& points);

		/*
		* �ݶ�ֵ
		*/
		Eigen::VectorXd G_X(const std::vector<Eigen::Vector3d>& points);

		/* ��ȡ ���
		*/
		void Copy(void* ele);

	public:
		GradientConeFitter(const Fitting::Cone &c);
	};
}


#endif // !GRADIENTCONE_H_H
