#ifndef TESTCYLINDER_H_H
#define TESTCYLINDER_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;

	class TestCylinder:public TestBase {
	protected:
		Cylinder fitResult, ans;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // TESTCYLINDER_H_H