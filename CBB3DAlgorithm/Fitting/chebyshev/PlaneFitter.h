#ifndef CHEBYSHEVFITTIINGPLANE_H_H
#define CHEBYSHEVFITTIINGPLANE_H_H
#include "../FittingBase.h"

namespace Chebyshev {
	class PlaneFitter : public Fitting::FittingBase  {
		Fitting::Plane plane;
		Fitting::Matrix Jacobi(const std::vector<Eigen::Vector3d>& points);

		/* beforHook
		* 每次迭代前的准备工作
		*/
		void beforHook(const std::vector<Eigen::Vector3d>& points);

		/* afterHook
		* 迭代后更新答案
		*/
		void afterHook(const Eigen::VectorXd& xp);


		/* 获取 d数组
		*/
		Eigen::VectorXd getDArray(const std::vector<Eigen::Vector3d>& points);

		// GetInitFit
		bool GetInitFit(const std::vector<Eigen::Vector3d>& points);
		
		/* F
		* 距离函数
		*/
		double F(const Eigen::Vector3d& p);

		/* 获取 最小二乘残差
		*/
		double  GetError(const std::vector<Eigen::Vector3d>& points);

		/* 获取 结果
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
