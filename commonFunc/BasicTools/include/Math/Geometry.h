#pragma once

#include "Eigen/Core"

namespace BasicTools
{
	int PointProjectPlane(Eigen::Vector3d& p, const Eigen::Vector3d& pInPlane, const Eigen::Vector3d& normal);
}

