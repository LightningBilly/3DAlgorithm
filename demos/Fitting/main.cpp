#include "gauss.h"
#include "chebyshev.h"
#include <string>
#include <stdio.h>
using namespace std;


int main(int argc, char** argv) {
	if (argc < 2) {
		puts("cmd: ");
		puts("fittingLine");
		puts("xmlCaseGen");
		puts("xmlAnsGen");
		puts("guassTestAll");
		puts("FittingLineTest");
		puts("FittingPlanePCATest");
		puts("FittingPlaneTest");
		puts("FittingCircleTest");
		puts("FittingCylinderTest");
		puts("FittingConeTest");
		puts("FittingMaxCircleInTest");
		puts("ConvexLineTest");
		puts("chebyshevTestAll");
		puts("Chebyshev::LineTest");
		puts("Chebyshev::CircleTest");
		puts("Chebyshev::PlaneTest");
		puts("Chebyshev::CylinderTest");
		puts("Chebyshev::SphereTest");
		return 0;
	}
	string func = string(argv[1]);
	if (func == "fittingLine") FittingLinePCATest();
	if (func == "xmlCaseGen") xmlCaseGen(argc, argv);
	if (func == "xmlAnsGen") xmlAnsGen(argc, argv);
	if (func == "guassTestAll") guassTestAll(argc, argv);
	if (func == "FittingLineTest") FittingLineTest(argc, argv);
	if (func == "FittingPlanePCATest") FittingPlanePCATest(argc, argv);
	if (func == "FittingPlaneTest") FittingPlaneTest(argc, argv);
	if (func == "FittingCircle2DTest") FittingCircle2DTest(argc, argv);
	if (func == "FittingSphereTest") FittingSphereTest(argc, argv);
	if (func == "FittingCircleTest") FittingCircleTest(argc, argv);
	if (func == "FittingCylinderTest") FittingCylinderTest(argc, argv);
	if (func == "FittingConeTest") FittingConeTest(argc, argv);
	if (func == "FittingMaxCircleInTest") FittingMaxCircleInTest(argc, argv);
	if (func == "ConvexLineTest") ConvexLineTest(argc, argv);
	if (func == "chebyshevTestAll") chebyshevTestAll(argc, argv);
	if (func == "Chebyshev::LineTest") Chebyshev::LineTest(argc, argv);
	if (func == "Chebyshev::CircleTest") Chebyshev::CircleTest(argc, argv);
	if (func == "Chebyshev::PlaneTest") Chebyshev::PlaneTest(argc, argv);
	if (func == "Chebyshev::CylinderTest") Chebyshev::CylinderTest(argc, argv);
	if (func == "Chebyshev::SphereTest") Chebyshev::SphereTest(argc, argv);
	return 0;
}

// ./FittingRun.exe  xmlCaseGen  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\TestData.xml" "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\data\\" "gauss"
// ./FittingRun.exe  xmlAnsGen  "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\Result.xml" "D:\selfad\alg_and_graph\3DAlgorithm\CBB3DAlgorithm\Fitting\gauss\answer\\" "gauss"

// ./FittingRun.exe  xmlCaseGen  "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\PtbTestData.xml" "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\data\\" "chebyshev"
// ./FittingRun.exe  xmlCaseGen  "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\切比雪夫测试数据.xml" "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\data-origin\\" "chebyshev"
// ./FittingRun.exe  xmlAnsGen  "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\PtbAlogProcessData.xml" "D:\shining3d\doc\检测软件测试结果\chebyshev\正式测试\fitting_result_app\\" "chebyshev"
