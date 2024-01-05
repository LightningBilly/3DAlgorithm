#include <Eigen/Core>
#include <vector>


namespace Fitting {
	class FittingBase {
	protected:
		/* getCenter
			获取点云中心
		 */
		Eigen::Vector3d getCenter(const std::vector<Eigen::Vector3d> &points);
		
		/* moveCenter
		* 将中心移至0点
		*/
		void moveCenter(const Eigen::Vector3d points);
		/* Jacobi
		* 构造jacobi矩阵
		*/
		
		/* findNext
		*	迭代1次得到解delta
		*/
		Eigen::VectorXd findNext(const Eigen::VectorXd &a0, const std::vector<Eigen::Vector3d>& points);

		/* beforHook
		* 每次迭代前的准备工作
		*/
		void beforHook(const Eigen::VectorXd& a0, const std::vector<Eigen::Vector3d>& points);
		
		/* afterHook
		* 迭代后更新答案
		*/
		void beforHook(const Eigen::VectorXd& p, Eigen::VectorXd &x0);

		// getRotationByOrient(Eigen::Vector3d orient);
		Eigen::Matrix3d getRotationByOrient(Eigen::Vector3d orient);
		
		/* 获取 d数组
		*/
		Eigen::VectorXd getDArray(const Eigen::VectorXd& a0, const std::vector<Eigen::Vector3d>& points);
		 
		// GetInitFit
		double GetInitFit(const std::vector<Eigen::Vector3d>& points, void* ele);
		// iteration
		double iteration(Eigen::VectorXd &x0, const std::vector<Eigen::Vector3d>& points);

	public:
		// Fitting
		double Fitting(const std::vector<Eigen::Vector3d>& points, void* ele);

		/* F
		* 距离函数
		*/
		double F(const Eigen::VectorXd& a0, const Eigen::Vector3d& p);

		/* 获取 最小二乘残差
		*/
		double  GetError(void* ele, const std::vector<Eigen::Vector3d>& points);
	};
}