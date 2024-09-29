#include "TestSphere.h"
#include "SphereFitter.h"
#include <iostream>

namespace Gauss {

	double TestSphere::Fitting() {
		Fitting::FittingBase* fb = new Gauss::SphereFitter();
		auto err = fb->Fitting(points, &fitResult);
		return err;
	}
	bool TestSphere::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!positionCmp(ans.center, fitResult.center))return false;
		if (!radiusCmp(ans.r, fitResult.r))return false;
		return true;
	}
	void TestSphere::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.center[i] = nums[i];
			ans.r = nums[3];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestSphere::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.center);
		writeNumber(fp, fitResult.r);
	}
}