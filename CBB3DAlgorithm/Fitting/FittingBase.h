#include <Eigen/Core>
#include <vector>


namespace Fitting {
	class FittingBase {
	protected:
		/* getCenter
			��ȡ��������
		 */
		Eigen::Vector3d getCenter(const std::vector<Eigen::Vector3d> &points);
		
		/* moveCenter
		* ����������0��
		*/
		void moveCenter(const Eigen::Vector3d points);
		/* Jacobi
		* ����jacobi����
		*/
		
		/* findNext
		*	����1�εõ���delta
		*/
		Eigen::VectorXd findNext(const Eigen::VectorXd &a0, const std::vector<Eigen::Vector3d>& points);

		/* beforHook
		* ÿ�ε���ǰ��׼������
		*/
		void beforHook(const Eigen::VectorXd& a0, const std::vector<Eigen::Vector3d>& points);
		
		/* afterHook
		* ��������´�
		*/
		void beforHook(const Eigen::VectorXd& p, Eigen::VectorXd &x0);

		// getRotationByOrient(Eigen::Vector3d orient);
		Eigen::Matrix3d getRotationByOrient(Eigen::Vector3d orient);
		
		/* ��ȡ d����
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
		* ���뺯��
		*/
		double F(const Eigen::VectorXd& a0, const Eigen::Vector3d& p);

		/* ��ȡ ��С���˲в�
		*/
		double  GetError(void* ele, const std::vector<Eigen::Vector3d>& points);
	};
}