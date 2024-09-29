#ifndef CHEBYSHEVTESTSPHERE_H_H
#define CHEBYSHEVTESTSPHERE_H_H

#include "../TestCase.h"

using namespace std;

namespace Chebyshev {
	using namespace Fitting;

	class TestSphere:public TestBase {
	protected:
		Sphere fitResult, ans;
		double formDis, formDisAns;
	public:
		virtual double Fitting();
		bool JudgeAnswer(FILE* fp);
		void ReadAnswer();
		void SaveAnswer(FILE* fp);
	};
}

#endif // CHEBYSHEVTESTSPHERE_H_H