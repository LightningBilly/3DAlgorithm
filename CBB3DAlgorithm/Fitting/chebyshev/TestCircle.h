#ifndef CHEBYSHEVTESTCIRCLE_H_H
#define CHEBYSHEVTESTCIRCLE_H_H

#include "../TestCase.h"

using namespace std;

namespace Chebyshev {
	using namespace Fitting;
	class TestCircle:public TestBase {
		Circle2D fitResult, ans;
		double formDis, formDisAns;
	public:
		double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};

}

#endif // CHEBYSHEVTESTCIRCLE_H_H