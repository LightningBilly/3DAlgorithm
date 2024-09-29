#include "TestAllCase.h"
#include "TestLine.h"
#include "TestPlane.h"
#include "TestSphere.h"
#include "TestCircle.h"
#include "TestCylinder.h"
#include "TestCone.h"

namespace Gauss {

	Fitting::TestBase* getTestObj(string kind) {
		TestBase* obj=NULL;
		if (kind == "LINE_3D")obj = new TestLinePCA();
		//if (kind == "PLANE")obj = new TestPlanePCA();
		if (kind == "PLANE")obj = new TestPlane();
		if (kind == "SPHERE")obj = new TestSphere();
		if (kind == "CIRCLE")obj = new TestCircle();
		if (kind == "CYLINDER")obj = new TestCylinder();
		if (kind == "CONE")obj = new TestCone();

		return obj;
	}

	void TestAllCase() {
		string caseDir = "D:/selfad/alg_and_graph/3DAlgorithm/CBB3DAlgorithm/Fitting/gauss/";

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
