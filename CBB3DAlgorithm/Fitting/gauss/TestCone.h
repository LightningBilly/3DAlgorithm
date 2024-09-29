#ifndef TESTCONE_H_H
#define TESTCONE_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;

	class TestCone:public TestBase {
	protected:
		Cone fitResult, ans;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // TESTCONE_H_H