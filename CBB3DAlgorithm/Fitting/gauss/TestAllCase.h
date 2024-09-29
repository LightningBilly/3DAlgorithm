#ifndef TESTALLCASE_H_H
#define TESTALLCASE_H_H
#include "../TestCase.h"

namespace Gauss {
	Fitting::TestBase* getTestObj(string kind);

	void TestAllCase();
}

#endif // TESTALLCASE_H_H