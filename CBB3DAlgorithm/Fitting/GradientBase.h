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
		* �趨��ʼֵ����ȡ������
		*/
		virtual VK initVK() = 0;

		/*transResult
		* ���½�
		*/
		virtual void transResult(const VK & xk)=0;

		/* F
		* ����ֵ
		*/
		virtual double F_X(const std::vector<Eigen::Vector3d>& points)=0;

		/*
		* �ݶ�ֵ
		*/
		virtual Eigen::VectorXd G_X(const std::vector<Eigen::Vector3d>& points)=0;

		/* ��ȡ ���
		*/
		virtual void Copy(void* ele) = 0;

	public:
		// �ݶ��½�����
		double Descending(const std::vector<Eigen::Vector3d>& points, void* ele);
	};
}

#endif // !FITTINGBASE_H_H
