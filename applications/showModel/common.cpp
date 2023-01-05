#include "common.h"
#include <cmath>

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

void ShowVTKLines(acamcad::VTK& vtk) {
    
}