#ifndef CHEBYSHEVTESTCYLINDER_H_H
#define CHEBYSHEVTESTCYLINDER_H_H

#include "../TestCase.h"

using namespace std;

namespace Chebyshev {
	using namespace Fitting;

	class TestCylinder:public TestBase {
	protected:
		Cylinder fitResult, ans;
		double formDis, formDisAns;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // CHEBYSHEVTESTCYLINDER_H_H