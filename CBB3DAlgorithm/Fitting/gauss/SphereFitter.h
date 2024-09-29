#ifndef FITTIINGSPHERE_H_H
#define FITTIINGSPHERE_H_H
#include "../FittingBase.h"

namespace Gauss {
	double F(Fitting::Sphere sphere, const Point &p);
	double GetError(Fitting::Sphere sphere, const std::vector<Eigen::Vector3d>& points);
	class SphereFitter: public Fitting::FittingBase  {
		Fitting::Sphere sphere;
		Fitting::Matrix Jacobi(const std::vector<Eigen::Vector3d>& points);

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


#endif // !FITTIINGSPHERE_H_H
