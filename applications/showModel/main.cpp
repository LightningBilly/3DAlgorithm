#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "model.h"
#include <cmath>
#include "IOManager.h"
#include <limits.h>
#include <numeric>
#include<algorithm>
#include <corecrt_math_defines.h>
#include<include/VTK/vtk.h>
#include<include/math/MMatrix3.h>
#include"common.h"
using namespace std;

#define  ColoredVertex(c,v) do{ glColor3fv(c); glVertex3fv(v); }while(0)
PolyMesh* mesh;

// char *path = "D:/selfad/3DAlgorithm/applications/showModel/d.txt";
// char* path = "D:/selfad/3DAlgorithm/CBB3DAlgorithm/MVCParameterization/src/Bunny_head.obj";
char* path = "D:/selfad/3DAlgorithm_build/lscm/build/Release/human_lscm.obj";
//ObjectModel om(path);

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    //如果按下ESC，把windowShouldClose设置为True，外面的循环会关闭应用
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        std::cout << "ESC" << mode;
    }

    if (action != GLFW_PRESS)return;
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case  GLFW_KEY_D:
    {

    }
    break;
    default:
        break;
    }

}

int moving = 0;
double sx = 0, sy = 0, angy = 0, angx = 0;

void mouse_click(GLFWwindow * window, int button, int action, int mods) {
    cout << button << "," << action << "," << mods << endl;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    sx = xpos;
    sy = ypos;
    cout << xpos / 300 - 1 << "," << 1 - ypos / 300 << endl;
    cout << xpos << "," << ypos << endl;
    //om.getPointWithLine(Vector3(xpos / 300 - 1, 1 - ypos / 300, 0), Vector3(0, 0, -1));
    moving = action;
}


MVector3 cal_circum_enter(const MVector3 & a, const MVector3 & b, const MVector3 & c)
{
    MVector3 ac = c - a, ab = b - a;
    MVector3 abXac = cross(ab, ac), abXacXab = cross(abXac, ab), acXabXac = cross(ac, abXac);
    return a + (abXacXab * ac.normSq() + acXabXac * ab.normSq()) / (2.0 * abXac.normSq());
}

void cal_local_ave_region(PolyMesh* const mesh, std::vector<double> &vertexLAR)
{
    vertexLAR.assign(mesh->numVertices(), 0);

    for (auto v : mesh->vertices()) {
        auto ps = mesh->vertAdjacentPolygon(v);
        if (ps.size() == 0)continue;

        auto n = ps[0]->normal();
        for (int i = 1; i < ps.size(); i++) n += ps[i]->normal();
        n /= ps.size();
        v->setNormal(n);
    }

    for (MPolyFace* fh : mesh->polyfaces())
    {
        // judge if it's obtuse
        bool isObtuseAngle = false;
        MVert* obtuseVertexHandle;
        MHalfedge* he = fh->halfEdge();
        MHalfedge* he_next = he->next(), * he_prev = he->prev();
        MVert* v_from_he = he->fromVertex(), * v_from_he_next = he_next->fromVertex(), * v_from_he_prev = he_prev->fromVertex();
        MVector3 vec_he_nor = he->tangent(), vec_he_next_nor = he_next->tangent(), vec_he_prev_nor = he_prev->tangent();
        if (vectorAngle(vec_he_nor, -vec_he_prev_nor) > M_PI / 2.0)
        {
            isObtuseAngle = true;
            obtuseVertexHandle = v_from_he;
        }
        else if (vectorAngle(vec_he_next_nor, -vec_he_nor) > M_PI / 2.0)
        {
            isObtuseAngle = true;
            obtuseVertexHandle = v_from_he_next;
        }
        else if (vectorAngle(vec_he_prev_nor, -vec_he_next_nor) > M_PI / 2.0)
        {
            isObtuseAngle = true;
            obtuseVertexHandle = v_from_he_prev;
        }

        // calculate area
        if (isObtuseAngle)
        {
            double faceArea = 0.5 * norm(cross(v_from_he_next->position() - v_from_he->position(), v_from_he_prev->position() - v_from_he->position()));
            for (MVert* fv : mesh->polygonVertices(fh))
            {
                if (fv == obtuseVertexHandle)
                    vertexLAR[fv->index()] += faceArea / 2.0;
                else
                    vertexLAR[fv->index()] += faceArea / 4.0;
            }
        }
        else
        {
            MVector3 cc = cal_circum_enter(v_from_he->position(), v_from_he_next->position(), v_from_he_prev->position());
            for (MHalfedge* fhh : mesh->polygonHalfedges(fh))
            {
                MVector3 edgeMidpoint = 0.5 * (fhh->fromVertex()->position() + fhh->toVertex()->position());
                double edgeLength = fhh->edge()->length();
                double partArea = 0.5 * edgeLength * (edgeMidpoint - cc).norm();
                vertexLAR[fhh->fromVertex()->index()] += 0.5 * partArea;
                vertexLAR[fhh->toVertex()->index()] += 0.5 * partArea;
            }
        }


    }
}

void cal_mean_curvature(PolyMesh* const mesh, const std::vector<double> &vertexLAR, std::vector<double> &meanCur, std::vector<double> &absMeanCur)
{
    meanCur.assign(mesh->numVertices(), 0);
    absMeanCur.assign(mesh->numVertices(), 0);
    for (MVert* vh : mesh->vertices())
    {
        MVector3 p_temp = { 0.0,0.0,0.0 }, p_vh = vh->position();
        for (auto voh_it = mesh->voh_iter(vh); voh_it.isValid(); ++voh_it)
        {
            if (!(*voh_it)->isBoundary())
            {
                MHalfedge* next_voh = (*voh_it)->next();
                MVert* to_voh = (*voh_it)->toVertex(), * to_next_voh = next_voh->toVertex();
                MVector3 p_to_voh = to_voh->position(), p_to_next_voh = to_next_voh->position();
                double angle_voh = vectorAngle(p_vh - p_to_voh, p_to_next_voh - p_to_voh),
                    angle_next_voh = vectorAngle(p_to_voh - p_to_next_voh, p_vh - p_to_next_voh);
                p_temp += (p_to_next_voh - p_vh) / tan(angle_voh);
                p_temp += (p_to_voh - p_vh) / tan(angle_next_voh);
            }
        }
        p_temp /= 4 * vertexLAR[vh->index()];
        if (dot(p_temp, vh->normal()) > 0)
            meanCur[vh->index()] = -p_temp.norm();
        else
            meanCur[vh->index()] = p_temp.norm();
        absMeanCur[vh->index()] = p_temp.norm();
    }

    std::cout << "Calculate Mean Curvature Done" << std::endl;
    std::cout << "Calculate Absolute Mean Curvature Done" << std::endl;
}


void cal_gaussian_curvature(PolyMesh* const mesh, const std::vector<double> &vertexLAR, std::vector<double> &gaussianCur)
{
    gaussianCur.assign(mesh->numVertices(), 0);
    for (MVert* vh : mesh->vertices())
    {
        double angle_temp = 2 * M_PI;
        MVector3  p_vh = vh->position();
        for (auto voh_it = mesh->voh_iter(vh); voh_it.isValid(); ++voh_it)
        {
            if (!(*voh_it)->isBoundary())
            {
                MHalfedge* next_voh = (*voh_it)->next();
                MVert* to_voh = (*voh_it)->toVertex(), * to_next_voh = next_voh->toVertex();
                MVector3 p_to_voh = to_voh->position(), p_to_next_voh = to_next_voh->position();
                double angle = vectorAngle(p_to_voh - p_vh, p_to_next_voh - p_vh);
                angle_temp -= angle;
            }
        }
        angle_temp /= vertexLAR[vh->index()];
        gaussianCur[vh->index()] = angle_temp;
    }
    std::cout << "Calculate Gaussian Curvature Done" << std::endl;
}

int main(void) {
    auto r = new OBJReader();
    mesh = new PolyMesh();
    r->read(path, mesh);
    
    std::vector<double> meanCur, absMeanCur, gaussianCur;
    std::vector<double> vertexLAR;
    cal_local_ave_region(mesh, vertexLAR);
    cal_mean_curvature(mesh, vertexLAR, meanCur, absMeanCur);
    cal_gaussian_curvature(mesh, vertexLAR, gaussianCur);
    for (auto v : meanCur) {
        // cout << v << endl;
    }
    mesh->scale(1);
    double m = *max_element(meanCur.begin(), meanCur.end());
    double mi = *min_element(meanCur.begin(), meanCur.end());
    // sort(meanCur.begin(), meanCur.end());
    for (int i = 0; i < meanCur.size(); i++) {
        meanCur[i] = (meanCur[i] - mi) * 1000 / (m - mi);
        // cout << meanCur[i] << endl;
    }
    cout << mi << endl;
    //return 0;
    m = *max_element(absMeanCur.begin(), absMeanCur.end());
    // sort(meanCur.begin(), meanCur.end());
    for (int i = 0; i < absMeanCur.size(); i++) {
        absMeanCur[i] = absMeanCur[i] * 1000 / m;
        // cout << absMeanCur[i] << endl;
    }


    acamcad::VTK vtk;
    vtk.add_line(acamcad::MPoint3(0, 0, 0), acamcad::MPoint3(1, 1, 1));
    vtk.add_line(acamcad::MPoint3(0, 0, 0), acamcad::MPoint3(1, 0, 0));
    vtk.add_line(acamcad::MPoint3(0, 0, 0), acamcad::MPoint3(0, 1, 0));
    vtk.add_line(acamcad::MPoint3(0, 0, 0), acamcad::MPoint3(0, 0, 1));
    // vtk.read_lines("D:/lines.vtk");

    // 点0.5,0,0.5 沿1，1，1旋转90度
    acamcad::RigidRTMatrix rt(acamcad::Point(0, 0, 0), acamcad::Point(1, 1, 1), 90);
    auto p = rt.Trans(acamcad::Point( 0.5, 0, 0.5 ));
/*
    auto w = new OBJWriter();
    w->write(writePath, mesh);
  */
  //初始化GLFW库
    if (!glfwInit())
        return -1;
    //创建窗口以及上下文
    GLFWwindow* window = glfwCreateWindow(900, 900, "hello world", NULL, NULL);
    if (!window) {
        //创建失败会返回NULL
        glfwTerminate();
    }

    //建立当前窗口的上下文
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); //注册回调函数
    glfwSetMouseButtonCallback(window, mouse_click);
    //glViewport(0, 0, 400, 400);
    //gluOrtho2D(-200, 200.0, -200, 200.0);
    //循环，直到用户关闭窗口


    while (!glfwWindowShouldClose(window)) {
        /*******轮询事件*******/
        glfwPollEvents();
        // cout<<456<<endl;
        //选择清空的颜色RGBA
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (moving && ypos > 0 && xpos > 0 && (fabs(ypos - sy) > 2 || (fabs(xpos - sx) > 2))) {
            cout << "cur p" << xpos << "," << ypos << endl;
            angy += (sy - ypos) / 300 * 360 + 360;
            while (angy >= 360) angy -= 360;
            cout << "angley:" << angy << endl;


            angx += (sx - xpos) / 300 * 360 + 360;
            while (angx >= 360) angx -= 360;
            cout << "anglex:" << angx << endl;

            sx = xpos;
            sy = ypos;
        }

        /*
        sx = xpos/300-1;
        sy = -(ypos/300-1);
         */
        glClearColor(0, 0, 0, 1);
        // glColor3f(0,0, 0);
        glMatrixMode(GL_PROJECTION);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mesh->Draw(angy, angx, gaussianCur);
        for (int i = 0, n = 1000; i < n; i++) {
            auto rgb = getRGB(i);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            //glRectf(0.7, 1.0 * i / n - 0.2, 0.8, 1.0 * (i + 1) / n - 0.2);
        }

        //ShowVTKLines(vtk, angx, angy);

        double px1=0.5, py1=0, pz1=0.5;
        double px2=p.x(), py2=p.y(), pz2=p.z();
        pointTrance(px1, py1, pz1, angx, angy);
        pointTrance(px2, py2, pz2, angx, angy);
        glPointSize(4);
        glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex3f(px1, py1, pz1);
        glColor3f(0, 1, 0);
        glVertex3f(px2, py2, pz2);
        glEnd();

        glFlush();
        // RevolveTriangle();
//        glColor3f(1,0,0);
//        glPointSize(10);
//        glBegin(GL_POINTS);
//        glVertex3d(xpos/300-1, -ypos/300+1, -1 );
//        glEnd();
        // glGetFloatv()
        /******交换缓冲区，更新window上的内容******/
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
