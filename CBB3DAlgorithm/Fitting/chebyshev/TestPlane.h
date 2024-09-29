#ifndef CHEBYSHEVTESTPLANE_H_H
#define CHEBYSHEVTESTPLANE_H_H

#include "../TestCase.h"

using namespace std;

namespace Chebyshev {
	using namespace Fitting;
	/*
	∆Ω√Ê≤‚ ‘
	*/
	class TestPlane:public TestBase {
	protected:
		Plane fitResult, ans;
		double formDis, formDisAns;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};

}

#endif // CHEBYSHEVTESTPLANE_H_H