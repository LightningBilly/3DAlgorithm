#include "TestCone.h"
#include "ConeFitter.h"
#include <iostream>
#include <cmath>

namespace Gauss {

	double TestCone::Fitting() {
		Fitting::FittingBase* fb = new Gauss::ConeFitter();
		double err;
		err = fb->Fitting(points, &fitResult);
		fitResult.alpha *= 180 / M_PI;
		/*vector<double> nums;
		if (PointCloud::readNums((suffixName + "/fitting_result/" + fileName + ".txt"), nums)) 
		for (int i = 0; i < 3; ++i) fitResult.center[i] = nums[i];
		for (int i = 0; i < 3; ++i) fitResult.orient[i] = nums[i + 3];
		fitResult.r = nums[6];
		fitResult.alpha = nums[7];*/
		return err;
	}
	bool TestCone::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!lineCmp(ans.orient, ans.center, fitResult.center))return false;
		if (!orientationCmp(ans.orient, fitResult.orient))return false;
		if (!radiusCmp(ans, fitResult))return false;
		if (!angleCmp(ans.alpha, fitResult.alpha))return false;
		return true;
	}
	void TestCone::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.center[i] = nums[i];
			for (int i = 0; i < 3; ++i) ans.orient[i] = nums[i+3];
			ans.r = nums[6];
			ans.alpha = nums[7];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestCone::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.center);
		writePoint(fp, fitResult.orient);
		writeNumber(fp, fitResult.r);
		writeNumber(fp, fitResult.alpha);
	}
}