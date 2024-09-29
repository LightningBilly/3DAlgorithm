#ifndef CHEBYSHEVFITTIINGCYLINDER_H_H
#define CHEBYSHEVFITTIINGCYLINDER_H_H
#include "../FittingBase.h"

namespace Chebyshev {
	class CylinderFitter: public Fitting::FittingBase  {
		static double F(Fitting::Cylinder cylinder, const Point& p);
		static double GetError(Fitting::Cylinder cylinder, const std::vector<Eigen::Vector3d>& points);
		Fitting::Cylinder cylinder;
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
	public:
		CylinderFitter();
	};
}


#endif // !FITTIINGCYLINDER_H_H
