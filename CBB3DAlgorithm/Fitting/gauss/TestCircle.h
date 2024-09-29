#ifndef TESTCIRCLE_H_H
#define TESTCIRCLE_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;

	class TestCircle:public TestBase {
	protected:
		Circle fitResult, ans;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // TESTCIRCLE_H_H