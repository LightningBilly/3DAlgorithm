#ifndef CHEBYSHEVTESTLINE_H_H
#define CHEBYSHEVTESTLINE_H_H

#include "../TestCase.h"

using namespace std;

namespace Chebyshev {
	using namespace Fitting;
	class TestLine:public TestBase {
		Line2D fitResult, ans;
		double formDis, formDisAns;
	public:
		double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};

}

#endif // CHEBYSHEVTESTLINE_H_H