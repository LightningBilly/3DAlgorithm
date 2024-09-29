#ifndef TESTLINE_H_H
#define TESTLINE_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;
	/*
	pca÷±œﬂ≤‚ ‘
	*/
	class TestLinePCA:public TestBase {
		Line fitResult, ans;
	public:
		double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};

}

#endif // TESTLINE_H_H