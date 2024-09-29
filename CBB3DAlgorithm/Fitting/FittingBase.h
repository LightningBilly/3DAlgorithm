#ifndef FITTINGBASE_H_H
#define FITTINGBASE_H_H

#include <Eigen/Core>
#include <vector>
#include "GeometryTypes.h"


namespace Fitting {
	enum FittingType {GAUSS, CHEBYSHEV, MAXIN, MINOUT};
	using Matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
	/* getCenter
		��ȡ��������
	 */
	Eigen::Vector3d getCenter(const std::vector<Eigen::Vector3d>& points);

	/* moveCenter
	* ����������0��
	*/
	void moveCenter(const Eigen::Vector3d center, std::vector<Eigen::Vector3d>& points);

	/* getRotationByOrient(Eigen::Vector3d orient);
	* ����һ����ת����ʹ��������Z��ƽ��
	*/ 
	Eigen::Matrix3d getRotationByOrient(Eigen::Vector3d orient);
	class FittingBase {
	protected:
		FittingType ft = FittingType::GAUSS; 
		double gamma=0; // chebyshevʹ��
		Eigen::Matrix3d U;
		std::vector<Eigen::Vector3d> transPoints;
		/* Jacobi
		* ����jacobi����
		*/
		virtual Matrix Jacobi(const std::vector<Eigen::Vector3d> &points)=0;
		
		/* findNext
		*	����1�εõ���delta
		*/
		Eigen::VectorXd findNext(const std::vector<Eigen::Vector3d>& points);


		/* beforHook
		* ÿ�ε���ǰ��׼������
		*/
		virtual void beforHook(const std::vector<Eigen::Vector3d>& points) {}
		
		/* afterHook
		* ��������´�
		*/
		virtual void afterHook(const Eigen::VectorXd& xp)=0;

		
		/* ��ȡ d����
		*/
		virtual Eigen::VectorXd getDArray(const std::vector<Eigen::Vector3d>& points)=0;
		 
		// GetInitFit �����Ƿ���ϳɹ�
		virtual bool GetInitFit(const std::vector<Eigen::Vector3d>& points)=0;
		// iteration
		double iteration(const std::vector<Eigen::Vector3d>& points);

		/* F
		* ���뺯��
		*/
		virtual double F(const Eigen::Vector3d& p)=0;

		/* ��ȡ ��С���˲в�
		*/
		virtual double  GetError(const std::vector<Eigen::Vector3d>& points) = 0;
		/* ��ȡ ���
		*/
		virtual void Copy(void* ele) = 0;

	public:
		// Fitting
		double Fitting(const std::vector<Eigen::Vector3d>& points, void* ele);
	};
}

#endif // !FITTINGBASE_H_H
