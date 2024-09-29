#ifndef POINTCLOUD_H_H
#define POINTCLOUD_H_H

#include <Eigen/Core>
#include <vector>
#include <string>
namespace PointCloud {
	bool readPoint(std::string fileName, std::vector<Eigen::Vector3d> &cld);
	bool writePoint(std::string fileName, std::vector<Eigen::Vector3d> &cld);
	bool readNums(std::string fileName, std::vector<double>& nums);
}
#endif // POINTCLOUD_H_H