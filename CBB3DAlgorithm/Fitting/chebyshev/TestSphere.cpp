#include "TestSphere.h"
#include "SphereFitter.h"
#include <iostream>

namespace Chebyshev {

	double TestSphere::Fitting() {
		Fitting::FittingBase* fb = new Chebyshev::SphereFitter();
		formDis = 2 * fb->Fitting(points, &fitResult);
		return formDis;
	}
	bool TestSphere::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!positionCmp(ans.center, fitResult.center))return false;
		if (!radiusCmp(ans.r, fitResult.r))return false;
		if (!formCmp(formDis, formDisAns))return false;
		return true;
	}
	void TestSphere::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.center[i] = nums[i];
			ans.r = nums[6];
			formDisAns = nums[7];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestSphere::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.center);
		writeNumber(fp, fitResult.r);
		writeNumber(fp, formDis);
	}
}