#include "TestLine.h"
#include "LineFitter.h"
#include <iostream>

namespace Chebyshev {

	double TestLine::Fitting() {

		Fitting::FittingBase* fb = new Chebyshev::LineFitter();
		formDis = 2 * fb->Fitting(points, &fitResult);
		return formDis;
		//return formDis=2*ConvexRotateFitting(points, fitResult);
	}
	bool TestLine::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!lineCmp2D(ans.Orient, ans.BasePoint, fitResult.BasePoint))return false;
		if (!orientationCmp2D(ans.Orient, fitResult.Orient))return false;
		if (!formCmp(formDis, formDisAns))return false;
		return true;
	}
	void TestLine::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 2; ++i) ans.BasePoint[i] = nums[i];
			for (int i = 0; i < 2; ++i) ans.Orient[i] = nums[3 + i];
			formDisAns = nums[6];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestLine::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.BasePoint);
		writePoint(fp, fitResult.Orient);
		writeNumber(fp, formDis);
	}
}