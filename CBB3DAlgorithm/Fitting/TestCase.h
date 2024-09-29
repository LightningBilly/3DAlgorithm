#ifndef TESTCASE_H_H
#define TESTCASE_H_H


#include<Eigen/Core>
#include <include/IOType/PointCloud.h>
#include "GeometryTypes.h"
#include<vector>

using namespace std;

namespace Fitting {
	const double POSITION_MAX_DST = 0.0001, ORIENTATION_MAX_DST = 0.0000001,
		ANGLE_MAX_DST = 0.0000001, RADIUS_MAX_DST = 0.0001, FORM_DIVATION=0.00001;

	void writePoint(FILE *fp, const Point &p);
	void writePoint(FILE *fp, const Eigen::Vector2d &p);
	void writeNumber(FILE *fp, double n);

	// �Ƚ�ƽ����Ƿ�һ��
	bool planeCmp(const Eigen::Vector3d& vec1, const Point& p1, const Point& p2);

	// �Ƚ�ֱ�ߵ��Ƿ�һ��
	bool lineCmp(const Eigen::Vector3d &vec1, const Point &p1, const Point &p2);
	bool lineCmp2D(const Eigen::Vector2d &vec1, const Eigen::Vector2d &p1, const Eigen::Vector2d &p2);
	// �Ƚϰ뾶
	bool radiusCmp(const Cone &cone1, const Cone &cone2);
	bool radiusCmp(double r1, double r2);
	// �ȽϷ����Ƿ�һ��
	bool orientationCmp(const Eigen::Vector3d &vec1, const Eigen::Vector3d& vec2);
	bool orientationCmp2D(const Eigen::Vector2d &vec1, const Eigen::Vector2d& vec2);
	// �ȽϽǶ�
	bool angleCmp(double angle1, double angle2);
	// �Ƚϵ�λ��
	bool positionCmp(const Point &p1, const Point &p2);
	bool positionCmp(const Eigen::Vector2d &p1, const Eigen::Vector2d &p2);
	// �Ƚ����
	bool formCmp(double d1, double d2);

	/*
	���Ի���
	*/
	class TestBase {
	protected:
		// ��������·�����ļ���
		string suffixName, fileName;
		vector<Point> points;
	public:
		TestBase() {}
		TestBase(string _suffixName, string _fileName): suffixName(_suffixName), fileName(_fileName) {}
		void SetFile(string _suffixName, string _fileName);

		void readPoints();
		virtual double Fitting()=0;
		virtual bool JudgeAnswer(FILE* fp) = 0;
		virtual void ReadAnswer() = 0;
		virtual void SaveAnswer(FILE* fp) = 0;
	};

}


#endif // !TESTCASE_H_H