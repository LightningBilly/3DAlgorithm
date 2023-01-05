#include "common.h"
#include <cmath>
#include "GL/glew.h"

void pointTrance(double& x, double& y, double& z, double angx, double angy) {
    double x1, y1, z1;
    // yÖáĞı×ª
    double ytheta = angy / 180 * 3.14;
    // cout<<"trance - angy" << angx<<endl;
    x1 = z * sin(ytheta) + x * cos(ytheta);
    y1 = y;
    z1 = z * cos(ytheta) - x * sin(ytheta);


    // xÖáĞı×ª
    double xtheta = angx / 180 * 3.14;

    x = x1;
    y = y1 * cos(xtheta) - z1 * sin(xtheta);
    z = y1 * sin(xtheta) + z1 * cos(xtheta);
}

void ShowVTKLines(acamcad::VTK& vtk, double angx, double angy) {


    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = 0; i < vtk.lines.size(); i += 2) {
        for (int j = 0; j < 2; ++j) {
            glColor3f(1, 1.0 * i / vtk.lines.size(), j);
            auto v = vtk.lines[i+j];
            double x = v[0], y = v[1], z = v[2];
            pointTrance(x, y, z, angx, angy);
            glVertex3d(x, y, z);
        }
    }
    glEnd();
}