#ifndef FITTINGBASE_H_H
#define FITTINGBASE_H_H

#include <Eigen/Core>
#include <vector>
#include "GeometryTypes.h"


namespace Fitting {
	enum FittingType {GAUSS, CHEBYSHEV, MAXIN, MINOUT};
	using Matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
	/* getCenter
		获取点云中心
	 */
	Eigen::Vector3d getCenter(const std::vector<Eigen::Vector3d>& points);

	/* moveCenter
	* 将中心移至0点
	*/
	void moveCenter(const Eigen::Vector3d center, std::vector<Eigen::Vector3d>& points);

	/* getRotationByOrient(Eigen::Vector3d orient);
	* 返回一个旋转矩阵使得向量与Z轴平行
	*/ 
	Eigen::Matrix3d getRotationByOrient(Eigen::Vector3d orient);
	class FittingBase {
	protected:
		FittingType ft = FittingType::GAUSS; 
		double gamma=0; // chebyshev使用
		Eigen::Matrix3d U;
		std::vector<Eigen::Vector3d> transPoints;
		/* Jacobi
		* 构造jacobi矩阵
		*/
		virtual Matrix Jacobi(const std::vector<Eigen::Vector3d> &points)=0;
		
		/* findNext
		*	迭代1次得到解delta
		*/
		Eigen::VectorXd findNext(const std::vector<Eigen::Vector3d>& points);


		/* beforHook
		* 每次迭代前的准备工作
		*/
		virtual void beforHook(const std::vector<Eigen::Vector3d>& points) {}
		
		/* afterHook
		* 迭代后更新答案
		*/
		virtual void afterHook(const Eigen::VectorXd& xp)=0;

		
		/* 获取 d数组
		*/
		virtual Eigen::VectorXd getDArray(const std::vector<Eigen::Vector3d>& points)=0;
		 
		// GetInitFit 返回是否拟合成功
		virtual bool GetInitFit(const std::vector<Eigen::Vector3d>& points)=0;
		// iteration
		double iteration(const std::vector<Eigen::Vector3d>& points);

		/* F
		* 距离函数
		*/
		virtual double F(const Eigen::Vector3d& p)=0;

		/* 获取 最小二乘残差
		*/
		virtual double  GetError(const std::vector<Eigen::Vector3d>& points) = 0;
		/* 获取 结果
		*/
		virtual void Copy(void* ele) = 0;

	public:
		// Fitting
		double Fitting(const std::vector<Eigen::Vector3d>& points, void* ele);
	};
}

#endif // !FITTINGBASE_H_H
