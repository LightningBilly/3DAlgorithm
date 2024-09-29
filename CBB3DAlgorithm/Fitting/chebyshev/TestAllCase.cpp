#include "TestAllCase.h"
#include "TestLine.h"
#include "TestCircle.h"
#include "TestPlane.h"
#include "TestCylinder.h"
#include "TestSphere.h"

namespace Chebyshev {

	Fitting::TestBase* getTestObj(string kind) {
		TestBase* obj=NULL;
		if (kind == "LINE_2D")obj = new TestLine();
		if (kind == "CIRCLE_2D")obj = new TestCircle();
		if (kind == "PLANE")obj = new TestPlane();
		if (kind == "SPHERE")obj = new TestSphere();
		if (kind == "CYLINDER")obj = new TestCylinder();

		return obj;
	}

	void TestAllCase() {
		string caseDir = "D:/selfad/alg_and_graph/3DAlgorithm/CBB3DAlgorithm/Fitting/chebyshev/chebyshev-testdata/officialtest/";

		FILE* caseList = fopen((caseDir+"data/kind.txt").c_str(), "r");
		char baseID[100], kind[100];
		FILE* testResult = fopen((caseDir + "fitting_result/result.txt").c_str(), "w");
		while (fscanf(caseList, "%s", baseID) != EOF) {
			strcpy(kind, baseID + 4);
			baseID[3] = 0;
			/*puts(baseID);
			puts(kind);*/

			Fitting::TestBase* testLogic = getTestObj(kind);
			if (testLogic == NULL)continue;
			fprintf(testResult, "%s : %s : ", baseID, kind);
			printf("%s : %s : ", baseID, kind);

			testLogic->SetFile(caseDir, baseID);


			testLogic->readPoints();
			testLogic->Fitting();
			FILE* ansfp = fopen((caseDir + "fitting_result/" + baseID + ".txt").c_str(), "w");
			testLogic->SaveAnswer(ansfp);
			
			fprintf(testResult, "%s\n", testLogic->JudgeAnswer(NULL)?"pass":"failed");
			printf("%s\n", testLogic->JudgeAnswer(NULL)?"pass":"failed");

			fclose(ansfp);
			delete testLogic;
		}

		fclose(caseList);
		fclose(testResult);
		puts("TEST COMPLETE");
	}
}
