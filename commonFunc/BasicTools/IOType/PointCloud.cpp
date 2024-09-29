#include "../include/IOType/PointCloud.h"
#include<stdio.h>
#include <iostream>


namespace PointCloud {
	bool readPoint(std::string fileName, std::vector<Eigen::Vector3d>& cld) {
        cld.clear();
        std::vector<double> nums;
        if (!readNums(fileName, nums))return false;

        cld.resize(nums.size() / 3);
        for (int i = 0; i < nums.size(); ++i) {
            cld[i / 3][i % 3] = nums[i];
        }

		return true;
	}

    bool writePoint(std::string fileName, std::vector<Eigen::Vector3d>& cld) {
        FILE* fp;
        fp = fopen(fileName.c_str(), "w");
        if (fp == NULL) {
            printf("open file %s: failed\n", fileName.c_str());
            return false;
        }

        for (auto& p : cld) {
            for (int i = 0; i < 3; ++i) {
                if (i)fprintf(fp, "\t");
                fprintf(fp, "%.16f", p[i]);
            }
            fprintf(fp, "\n");
        }

        return true;
    }

    bool readNums(std::string fileName, std::vector<double>& nums) {
        nums.clear();
        FILE* fp;
        fp = fopen(fileName.c_str(), "r");
        if (fp == NULL) {
            printf("open file %s: failed\n", fileName.c_str());
            return false;
        }
        double num;
        while (fscanf(fp, "%lf", &num) != EOF) {
            nums.push_back(num);
        }

        fclose(fp);
        return true;
    }
}