#include "TestLine.h"
#include "FittingLinePCA.h"
#include <iostream>

namespace Gauss {

	double TestLinePCA::Fitting() {
		return FittingPCA(points, fitResult);
	}
	bool TestLinePCA::JudgeAnswer(FILE* fp) {
		ReadAnswer();
		if (!lineCmp(ans.Orient, ans.BasePoint, fitResult.BasePoint))return false;
		if (!orientationCmp(ans.Orient, fitResult.Orient))return false;
		return true;
	}
	void TestLinePCA::ReadAnswer() {
		vector<double> nums;
		if (PointCloud::readNums((suffixName + "/answer/" + fileName + ".txt"), nums)) {
			for (int i = 0; i < 3; ++i) ans.BasePoint[i] = nums[i];
			for (int i = 0; i < 3; ++i) ans.Orient[i] = nums[3 + i];
		}
		else {
			std::cout << "read answer error" << std::endl;
		}
	}
	void TestLinePCA::SaveAnswer(FILE* fp) {
		writePoint(fp, fitResult.BasePoint);
		writePoint(fp, fitResult.Orient);
	}
}