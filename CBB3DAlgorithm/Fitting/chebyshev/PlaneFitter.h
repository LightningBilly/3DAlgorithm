#ifndef CHEBYSHEVFITTIINGPLANE_H_H
#define CHEBYSHEVFITTIINGPLANE_H_H
#include "../FittingBase.h"

namespace Chebyshev {
	class PlaneFitter : public Fitting::FittingBase  {
		Fitting::Plane plane;
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
		PlaneFitter();

	public:
		static double F(Fitting::Plane plane, const Point& p);
		static double GetError(Fitting::Plane plane, const std::vector<Eigen::Vector3d>& points);
	};

	double ConvexRotateFitting(const std::vector<Eigen::Vector3d>& points, Fitting::Line2D &line);
}


#endif // !CHEBYSHEVFITTIINGPLANE_H_H
