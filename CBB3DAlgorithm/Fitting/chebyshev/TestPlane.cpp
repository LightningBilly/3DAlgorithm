#include "TestPlane.h"
#include "PlaneFitter.h"
#include <iostream>

namespace Chebyshev {
	double TestPlane::Fitting() {
		Fitting::FittingBase* fb = new Chebyshev::PlaneFitter();
		formDis = 2 * fb->Fitting(points, &fitResult);
		return formDis;
	}
	bool TestPlane::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!planeCmp(ans.Orient, ans.BasePoint, fitResult.BasePoint))return false;
		if (!orientationCmp(ans.Orient, fitResult.Orient))return false;
		return true;
	}
	void TestPlane::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.BasePoint[i] = nums[i];
			for (int i = 0; i < 3; ++i) ans.Orient[i] = nums[3 + i];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestPlane::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.BasePoint);
		writePoint(fp, fitResult.Orient);
		writeNumber(fp, formDis);
	}
}