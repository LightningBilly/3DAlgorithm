#include "TestCircle.h"
#include "CircleFitter.h"
#include <iostream>

namespace Chebyshev {

	double TestCircle::Fitting() {
		Fitting::FittingBase* fb = new Chebyshev::CircleFitter();
		formDis = 2*fb->Fitting(points, &fitResult);
		return formDis;
	}
	bool TestCircle::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!positionCmp(ans.center, fitResult.center))return false;
		if (!radiusCmp(ans.r, fitResult.r))return false;
		if (!formCmp(formDis, formDisAns))return false;
		return true;
	}
	void TestCircle::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 2; ++i) ans.center[i] = nums[i];
			ans.r = nums[3];
			formDisAns = nums[4];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestCircle::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.center);
		writeNumber(fp, fitResult.r);
		writeNumber(fp, formDis);
	}
}