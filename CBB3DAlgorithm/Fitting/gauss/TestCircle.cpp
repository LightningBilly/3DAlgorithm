#include "TestCircle.h"
#include "CircleFitter.h"
#include <iostream>

namespace Gauss {

	double TestCircle::Fitting() {
		Fitting::FittingBase* fb = new Gauss::CircleFitter();
		auto err = fb->Fitting(points, &fitResult);
		return err;
	}
	bool TestCircle::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!positionCmp(ans.center, fitResult.center))return false;
		if (!orientationCmp(ans.orient, fitResult.orient))return false;
		if (!radiusCmp(ans.r, fitResult.r))return false;
		return true;
	}
	void TestCircle::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.center[i] = nums[i];
			for (int i = 0; i < 3; ++i) ans.orient[i] = nums[i+3];
			ans.r = nums[6];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestCircle::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.center);
		writePoint(fp, fitResult.orient);
		writeNumber(fp, fitResult.r);
	}
}