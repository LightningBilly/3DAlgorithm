#ifndef GEOMETRYTYPE_H_H
#define GEOMETRYTYPE_H_H

#include <Eigen/Core>

#define M_PI 3.14159265358979323846

typedef Eigen::Vector3d Point;
namespace Fitting {

	// 点法式表示直线
	class Line2D {
	public:
		Eigen::Vector2d BasePoint, Orient;
	};


	class Line {
	public:
		Eigen::Vector3d BasePoint, Orient;
		double len;
	};

	class Plane {
	public:
		Eigen::Vector3d BasePoint, Orient;
	};

	class Circle2D {
	public:
		Eigen::Vector2d center;
		double r;
	};

	class Sphere {
	public:
		Eigen::Vector3d center;
		double r;
	};


	class Circle {
	public:
		Eigen::Vector3d center, orient;
		double r;
	};

	class Cylinder {
	public:
		Eigen::Vector3d center, orient;
		double r;
	};


	class Cone{
	public:
		Eigen::Vector3d center, orient;
		double r, alpha, t; //t = r*cos(alpha/2)
	};

}
#endif