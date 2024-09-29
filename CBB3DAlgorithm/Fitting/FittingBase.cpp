#include "FittingBase.h"
#include <Eigen/Dense>
#include <include/Math/Simplex.h>
#include <iostream>

namespace Fitting {
	Eigen::Vector3d getCenter(const std::vector<Eigen::Vector3d>& points) {
		Eigen::Vector3d center = Eigen::Vector3d::Zero();
		for (auto& p : points) center += p;
		if (!points.empty())
			center /= points.size();

		return center;
	}

	void moveCenter(const Eigen::Vector3d center, std::vector<Eigen::Vector3d>& points) {
		for (auto& p : points) p -= center;
	}

	Eigen::Matrix3d getRotationByOrient(Eigen::Vector3d orient) {
		double s1 = 0, c1 = 1, s2 = -1, c2 = 0;
		if ((orient - Eigen::Vector3d(1, 0, 0)).norm() > 1e-6) {
			double a = orient.x();
			double b = orient.y();
			double c = orient.z();
			c1 = c / sqrt(b * b + c * c);
			s1 = -b / sqrt(b * b + c * c);
			c2 = (c * c1 - b * s1) / sqrt(a * a + pow(c * c1 - b * s1, 2));
			s2 = -a / sqrt(a * a + pow(c * c1 - b * s1, 2));
		}
		Eigen::Matrix3d U1;
		U1 << c2, 0, s2, 0, 1, 0, -s2, 0, c2;
		Eigen::Matrix3d U2;
		U2 << 1, 0, 0, 0, c1, s1, 0, -s1, c1;
		return U1 * U2;
	}

	Eigen::VectorXd FittingBase::findNext(const std::vector<Eigen::Vector3d>& points)
	{
		using namespace Eigen;
		Eigen::VectorXd xp;
		Eigen::VectorXd D = getDArray(points);
		Matrix J = Jacobi(points);
		if (ft == FittingType::CHEBYSHEV || ft == FittingType::MAXIN) {
			BasicTools::Simplex::LPS lps;
			int n = J.rows(), m = J.cols() * 2 + 1;
			std::vector<double> c(m,0); 
			c[m-1] = 1;// 令最后一位为gamma
			
			lps.InitProb(m, c, BasicTools::Simplex::MAX);
			
			// 添加条件
			if (ft == FittingType::MAXIN) {
				std::vector<double> x(m, -1);
				for (int i = 0; i < n; ++i) {
					// 系数 J(i, 0), -J(i, 0),J(i, 1), -J(i, 1), ...,-1
					for (int j = 0; j < J.cols(); ++j) {
						x[j * 2] = J(i, j);
						x[j * 2 + 1] = -x[j * 2];
					}
					lps.AddCondition(x, gamma - D(i), BasicTools::Simplex::GE);
				}
			}
			else // 切比雪夫
			{
				// 系数 J(i, 0), -J(i, 0),J(i, 1), -J(i, 1), ...,1 <= gamma-di
				std::vector<double> x(m, 1);
				// 系数 -J(i, 0), J(i, 0),-J(i, 1), J(i, 1), ...,1 <= gamma+di
				std::vector<double> x2(m, 1);
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < J.cols(); ++j) {
						x[j * 2] = J(i, j);
						x[j * 2 + 1] = -x[j * 2];
						x2[j * 2] = -x[j * 2];
						x2[j * 2+1] = -x[j * 2+1];
					}
					lps.AddCondition(x, gamma - D(i), BasicTools::Simplex::LE);
					lps.AddCondition(x2, gamma + D(i), BasicTools::Simplex::LE);

				}
			}
			auto res = lps.solve();
			xp.resize(J.cols()+1);
			xp.setZero();
			/*std::cout << res.Z << std::endl;
			std::cout << res.rt << std::endl;*/
			if (res.rt == BasicTools::Simplex::NoSolution || res.rt == BasicTools::Simplex::NoUpBound) return xp;
				xp(J.cols()) = res.x.back();
				for (int i = 0; i < J.cols(); ++i) xp(i) = res.x[i * 2] - res.x[i * 2 + 1];
			//}
		}
		else {
			// 求解 Jp = -D  https://blog.csdn.net/ABC_ORANGE/article/details/104489257/
			xp = J.colPivHouseholderQr().solve(-D);
			// xp = J.lu().solve(-D);
		}
		return xp;
	}

	double FittingBase::iteration(const std::vector<Eigen::Vector3d>& points)
	{
		transPoints = points;
		
		for (int i=50;i--;) {
			beforHook(points);
			Eigen::VectorXd xp = findNext(transPoints);
			if (xp.norm() < 1e-10)break;
			afterHook(xp);
		}

		return GetError(points);
	}

	double FittingBase::Fitting(const std::vector<Eigen::Vector3d>& points, void* ele)
	{
		// 获取初值
		if(!GetInitFit(points))return -1;

		// 高斯牛顿迭代
		double err = iteration(points);

		// 返回值
		Copy(ele);
		return err;
	}

}

