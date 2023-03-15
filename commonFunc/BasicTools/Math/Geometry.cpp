#include "../include/Math/Geometry.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace BasicTools {
	/*
	����ֱ�ߵ�ƽ���ϵĽ����߼�����
	https://blog.csdn.net/chenbb1989/article/details/122096088
	*/
	int PointProjectPlane(Eigen::Vector3d& p,const Eigen::Vector3d& pInPlane,const Eigen::Vector3d& normal) {
		assert(abs(normal.squaredNorm - 1) < 1e-6);
        double t = -(p - pInPlane).dot(normal);
        p = p + t * normal;
		return 0;
	}
}