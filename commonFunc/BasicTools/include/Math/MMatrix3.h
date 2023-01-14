#pragma once

// #include "MPoint3.h"
#include "Massage.h"
#include <vector>
#include "Eigen/Core"
#include <cmath>


namespace acamcad {
    const double pi = acos(-1);
    using Point = Eigen::Vector3d;
    class RigidRTMatrix {
    private:
        Eigen::Matrix3d mat;
        Eigen::Vector3d trans;
        
    public:
        
        RigidRTMatrix(Point start, Point end, double theta) {
            Eigen::Vector3d v = end - start;
            assert(!v.isZero());
            theta = angleMod(theta);
            // Point::Zero();
            v.normalize();
            Eigen::Vector3d X = {1,0,0};
            Eigen::Vector3d m = v.cross(X);
            auto RY = GetRY(m);
            // 将v 旋转至ZOX 平面。
            auto vZOX = RY * v;
            auto RX = GetRX(vZOX);

            // auto 
        }
        
        RigidRTMatrix() {

        }
        
        // 给定YOX平面上的单位M向量，将其旋转到Y轴上。
        Eigen::Matrix3d GetRY(Eigen::Vector3d m) {
            assert(!m.isZero());
            m.normalize();
            Eigen::Matrix3d RY;
            RY.setIdentity();
            RY(1, 1) = m.y();
            RY(1, 2) = m.z();
            RY(2, 1) = -m.z();
            RY(2, 2) = m.y();
            return RY;
        }

        // 给定ZOX平面上的单位M向量，将其旋转到X轴上。
        Eigen::Matrix3d GetRX(Eigen::Vector3d m) {
            assert(!m.isZero());
            m.normalize();
            Eigen::Matrix3d RX;
            RX.setIdentity();
            RX(0, 0) = m.x();
            RX(0, 2) = m.z();
            RX(2, 0) = -m.z();
            RX(2, 2) = m.x();
            return RX;
        }

        // 给定ZOX平面上的单位M向量，将其旋转到X轴上。
        Eigen::Matrix3d GetXRotate(double theta) {
            double rad = theta / 180 * pi;
            Eigen::Matrix3d X;
            X.setIdentity();
            X(1, 1) = cos(rad);
            X(1, 2) = sin(rad);
            X(2, 1) = -sin(rad);
            X(2, 2) = cos(rad);
            return X;
        }

        double angleMod(double theta) {
            while (theta < -180)theta += 360;
            while (theta > 180)theta -= 360;
            return theta;
        }

        friend static RigidRTMatrix operator*(RigidRTMatrix& a, RigidRTMatrix& b) {
            RigidRTMatrix multi;
            multi.mat = a.mat * b.mat;
            return multi;
        }
    };

	class MMatrix3
	{
    private:
        static const int S = 3;
        double mat[3][3];

    public:
        MMatrix3() {
            memset(mat, 0, sizeof(double) * 9);
        }
        
        MMatrix3(const std::vector<double> &v) {
            assert(v.size() >= S * S);
            int k = 0;
            for (int i = 0; i < S; ++i) {
                for (int j = 0; j < S; ++j) {
                    mat[i][j] = v[k++];
                }
            }
        }

        MMatrix3(const MMatrix3& v) {
            
        }

        void out() {
            printf("matrix\n");
        }
        /*

        MVector3& operator+=(const MVector3& a)
        {
            P[0] += a[0];
            P[1] += a[1];
            P[2] += a[2];
            return *this;
        }
        MVector3& operator-=(const MVector3& a)
        {
            P[0] -= a[0];
            P[1] -= a[1];
            P[2] -= a[2];
            return *this;
        }
        MVector3& operator*=(const MVector3& a)
        {
            P[0] *= a[0];
            P[1] *= a[1];
            P[2] *= a[2];
            return *this;
        }
        MVector3& operator*=(const double v)
        {
            P[0] *= v;
            P[1] *= v;
            P[2] *= v;
            return *this;
        }
        MVector3& operator/=(const double v)
        {
            P[0] /= v;
            P[1] /= v;
            P[2] /= v;
            return *this;
        }
        MVector3& operator=(const MVector3& a)
        {
            P[0] = a[0];
            P[1] = a[1];
            P[2] = a[2];
            return *this;
        }
        MVector3& operator=(double v)
        {
            P[0] = v;
            P[1] = v;
            P[2] = v;
            return *this;
        }

        MVector3 cross(const MVector3& b) const
        {
            return MVector3(y() * b.z() - b.y() * z(), -(x() * b.z() - b.x() * z()), x() * b.y() - b.x() * y());
        }

        double dot(const MVector3& b) const
        {
            return x() * b.x() + y() * b.y() + z() * b.z();
        }
        */

    };
    /*
    inline MVector3 operator%(const MVector3& a, const MVector3& b)
    {
        return MVector3(a.y() * b.z() - b.y() * a.z(),
            -(a.x() * b.z() - b.x() * a.z()),
            a.x() * b.y() - b.x() * a.y());
    }
    */
}

    //void print(const std::string& name = "") const
    //{
    //    Msg::Info("Vector \'%s\':  %f  %f  %f", name.c_str(), P[0], P[1], P[2]);
    //}