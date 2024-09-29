#ifndef FITTIINGCONE_H_H
#define FITTIINGCONE_H_H
#include "../FittingBase.h"

namespace Gauss {
	double F(Fitting::Cone cone, const Point &p);
	double GetError(Fitting::Cone cone, const std::vector<Eigen::Vector3d>& points);
	class ConeFitter: public Fitting::FittingBase  {
		Fitting::Cone cone;
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


#endif // !FITTIINGCONE_H_H
