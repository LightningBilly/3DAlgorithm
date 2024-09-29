#ifndef TESTPLANE_H_H
#define TESTPLANE_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;
	/*
	pca∆Ω√Ê≤‚ ‘
	*/
	class TestPlanePCA:public TestBase {
	protected:
		Plane fitResult, ans;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};

	class TestPlane :public TestPlanePCA {
	public:
		double Fitting();
	};
}

#endif // TESTPLANE_H_H