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
		* ÿ�ε���ǰ��׼������
		*/
		void beforHook(const std::vector<Eigen::Vector3d>& points);

		/* afterHook
		* ��������´�
		*/
		void afterHook(const Eigen::VectorXd& xp);


		/* ��ȡ d����
		*/
		Eigen::VectorXd getDArray(const std::vector<Eigen::Vector3d>& points);

		// GetInitFit
		bool GetInitFit(const std::vector<Eigen::Vector3d>& points);
		
		/* F
		* ���뺯��
		*/
		double F(const Eigen::Vector3d& p);

		/* ��ȡ ��С���˲в�
		*/
		double  GetError(const std::vector<Eigen::Vector3d>& points);

		/* ��ȡ ���
		*/
		void Copy(void* ele);
	};
}


#endif // !FITTIINGCIRCLE_H_H