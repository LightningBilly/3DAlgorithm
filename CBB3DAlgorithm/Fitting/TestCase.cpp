#include "TestCase.h"
#include <cmath>
#include <cmath>
#include <iostream>
#include <Eigen/Dense>


namespace Fitting {

	void writeNumber(FILE* fp, double n) {
		fprintf(fp, "%.16f\n", n);
	}

	void writePoint(FILE* fp, const Point& p) {
		for (int i = 0; i < p.size(); ++i) writeNumber(fp, p[i]);
	}

	void writePoint(FILE* fp, const Eigen::Vector2d& p)
	{
		for (int i = 0; i < p.size(); ++i) writeNumber(fp, p[i]);
	}

	bool planeCmp(const Eigen::Vector3d& vec1, const Point& p1, const Point& p2)
	{
		Eigen::Vector3d de = p1 - p2;
		double dis = abs(vec1.dot(de));
		//cout << dis << endl;
		return dis < POSITION_MAX_DST;
	}

	bool lineCmp(const Eigen::Vector3d& vec1, const Point& p1, const Point& p2) {
		Eigen::Vector3d de = p1 - p2;
		double dis = vec1.cross(de).norm();
		return dis < POSITION_MAX_DST;
	}

	bool lineCmp2D(const Eigen::Vector2d& vec1, const Eigen::Vector2d& p1, const Eigen::Vector2d& p2) {
		auto de = p1 - p2;
		double dis = abs(de.x() * vec1.y() - de.y() * vec1.x());
		//cout << dis << endl;
		return dis < POSITION_MAX_DST;
	}

	bool radiusCmp(const Cone& cone1, const Cone& cone2)
	{
		double r2 = cone2.r;
		double r1 = cone1.r - (cone2.center - cone1.center).dot(cone1.orient) * tan(cone1.alpha /2/180*M_PI);
		double dis = abs(r1 - r2);
		return dis<RADIUS_MAX_DST;
	}

	bool radiusCmp(double r1, double r2)
	{
		double dis = abs(r1 - r2);
		return dis < RADIUS_MAX_DST;
	}

	bool orientationCmp(const Eigen::Vector3d& vec1, const Eigen::Vector3d& vec2) {
		//cout << "alpha 1 :  " << vec1.dot(vec2) << endl;
		double cosv = vec1.dot(vec2);
		if (cosv > 1)cosv = 1;
		if (cosv < -1) cosv = -1;
		double alpha = acos(cosv);
		if (alpha > M_PI / 2) alpha = M_PI - alpha;
		//cout <<"alpha :  "<< alpha << endl;
		return alpha < ORIENTATION_MAX_DST;
	}


	bool orientationCmp2D(const Eigen::Vector2d& vec1, const Eigen::Vector2d& vec2) {
		double cosv = vec1.dot(vec2);
		if (cosv > 1)cosv = 1;
		if (cosv < -1) cosv = -1;
		double alpha = acos(cosv);
		if (alpha > M_PI / 2) alpha = M_PI - alpha;
		//cout << alpha << endl;
		return alpha < ORIENTATION_MAX_DST;
	}

	bool angleCmp(double angle1, double angle2)
	{
		double dis = abs(angle1 - angle2) / 180 * M_PI;
		return dis < ANGLE_MAX_DST;
	}

	bool positionCmp(const Point& p1, const Point& p2)
	{
		double dis = (p1-p2).norm();
		return dis < POSITION_MAX_DST;
	}
	
	bool positionCmp(const Eigen::Vector2d& p1, const Eigen::Vector2d& p2)
	{
		double dis = (p1-p2).norm();
		return dis < POSITION_MAX_DST;
	}

	bool formCmp(double d1, double d2) {
		return abs(d1 - d2) < FORM_DIVATION;
	}

	void TestBase::SetFile(string _suffixName, string _fileName) {
		suffixName = _suffixName;
		fileName = _fileName;
	}


	void TestBase::readPoints() {
		PointCloud::readPoint(suffixName + "/data/" + fileName + ".asc", points);
		//std::cout << points.size() << std::endl;
	}

}