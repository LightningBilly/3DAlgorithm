#ifndef TESTSPHERE_H_H
#define TESTSPHERE_H_H

#include "../TestCase.h"

using namespace std;

namespace Gauss {
	using namespace Fitting;

	class TestSphere:public TestBase {
	protected:
		Sphere fitResult, ans;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // TESTSPHERE_H_H