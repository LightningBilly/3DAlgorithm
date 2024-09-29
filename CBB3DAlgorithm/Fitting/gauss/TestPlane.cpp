#include "TestPlane.h"
#include "FittingPlanePCA.h"
#include "FittingPlane.h"
#include <iostream>

namespace Gauss {


	double TestPlane::Fitting() {
		Fitting::FittingBase* fb = new Gauss::FittingPlane();
		auto err = fb->Fitting(points, &fitResult);
		return err;
	}

	double TestPlanePCA::Fitting() {
		return FittingPCA(points, fitResult);
	}
	bool TestPlanePCA::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!planeCmp(ans.Orient, ans.BasePoint, fitResult.BasePoint))return false;
		if (!orientationCmp(ans.Orient, fitResult.Orient))return false;
		return true;
	}
	void TestPlanePCA::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.BasePoint[i] = nums[i];
			for (int i = 0; i < 3; ++i) ans.Orient[i] = nums[3 + i];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestPlanePCA::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.BasePoint);
		writePoint(fp, fitResult.Orient);
	}
}