#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

using namespace std;
#define PI 3.14
#define FOUR 4

bitset<FOUR> getPosCode(vector<double> bord, vector<double> coord) {
    bitset<FOUR> temp;
    if (bord.size() < FOUR && coord.size() < 2)
        throw logic_error("wrong size");
    if (coord[0] < bord[0])
        temp.set(3);
    if (coord[0] > bord[1])
        temp.set(2);
    if (coord[1] < bord[2])
        temp.set(1);
    if (coord[1] > bord[3])
        temp.set(0);
    return temp;
}

double getY(double B, vector<double> T1, vector<double> T2) {
    double C = (B - T1[0]) * (T2[1] - T1[1]);
    C = C / (T2[0] - T1[0]);
    C += T1[1];
    return C;
}

double getX(double B, vector<double> T1, vector<double> T2) {
    double C = (B - T1[1]) * (T2[0] - T1[0]);
    C = C / (T2[1] - T1[1]);
    C += T1[0];
    return C;
}

vector<double> getCross(vector<double> bord, vector<double> T1, vector<double> T2) {
    if (bord.size() < FOUR && T1.size() < 2 && T2.size() < 2)
        throw logic_error("bad size");
    vector<double> temp(2);
    if (T1[0] < bord[0]) {
        temp[0] = bord[0];
        temp[1] = getY(bord[0], T1, T2);
    }
    else if (T1[0] > bord[1]) {
        temp[0] = bord[1];
        temp[1] = getY(bord[1], T1, T2);
    }
    else if (T1[1] < bord[2]) {
        temp[0] = getX(bord[2], T1, T2);
        temp[1] = bord[2];
    }
    else if (T1[1] > bord[3]) {
        temp[0] = getX(bord[3], T1, T2);
        temp[1] = bord[3];
    }
    return temp;
}

enum inside_t { in = 1, out = -1, unknow = 0 };

inside_t insideCheck(vector<double> bord, vector<double> T1, vector<double> T2) {
    bitset<4> P1 = getPosCode(bord, T1);
    bitset<4> P2 = getPosCode(bord, T2);
    if (P1.to_ulong() == 0 && P2.to_ulong() == 0)
        return inside_t::in;
    if ((P1 & P2).to_ulong())
        return inside_t::out;
    return inside_t::unknow;
}



vector<vector<double>> clip(vector<double> bord, vector<double> T1, vector<double> T2) {
    if (bord.size() < FOUR && T1.size() < 2 && T2.size() < 2)
        throw logic_error("wrong size");
    vector<vector<double>> temp;
    vector<double> temp1 = T1;
    vector<double> temp2 = T2;
    bitset<4> P1;
    bitset<4> P2;
    inside_t flag = insideCheck(bord, temp1, temp2);
    while (flag == inside_t::unknow) {
        P1 = getPosCode(bord, temp1);
        //P2 = getPosCode(bord, temp2);
        if (P1.to_ulong() == 0) {
            swap(temp1, temp2);
        }
        else {
            temp1 = getCross(bord, temp1, temp2);
        }
        flag = insideCheck(bord, temp1, temp2);
    }
    if (flag == inside_t::in) {
        temp.push_back(temp1);
        temp.push_back(temp2);
    }
    return temp;
}

void drawLine(vector<vector<double>> line) {
    if (line.size() == 0)
        return;
    if (line.size() < 2 && line[0].size() < 2 && line[1].size() < 2)
        throw logic_error("wrong size");
    glBegin(GL_LINES);
    glVertex2d(line[0][0], line[0][1]);
    glVertex2d(line[1][0], line[1][1]);
    glEnd();
}

double rotX(vector<double> T, double angle) {
    return (T[0] * cos(angle * PI / 180.0) - T[1] * sin(angle * PI / 180.0));
}

double rotY(vector<double> T, double angle) {
    return (T[0] * sin(angle * PI / 180.0) + T[1] * cos(angle * PI / 180.0));
}

void display(void) {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    vector<double> bord(4);
    bord = { -0.5, 0.5, -0.5, 0.5 };// left, right, bottom, top
    glColor3f(0.5, 0.7, 0.3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(bord[0], bord[2]);
    glVertex2f(bord[1], bord[2]);
    glVertex2f(bord[1], bord[3]);
    glVertex2f(bord[0], bord[3]);
    glEnd();
    double h = 0.15;
    double w = 0.3;
    double d = 0.02;
    double pAngle = 60;
    double dAngle = 55;
    glColor3f(0.5, 0.7, 0.3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (int i = 0; i < 50; i++) {

        vector<double> T1 = { -w, -h }, T2 = { w, -h }, T3 = { w, h }, T4 = { -w, h };
        vector<double> M1 = { rotX(T1, pAngle), rotY(T1, pAngle) },
            M2 = { rotX(T2, pAngle), rotY(T2, pAngle) },
            M3 = { rotX(T3, pAngle), rotY(T3, pAngle) },
            M4 = { rotX(T4, pAngle), rotY(T4, pAngle) };

        vector<vector<double>> bottomL = clip(bord, M1, M2);
        vector<vector<double>> rightL = clip(bord, M2, M3);
        vector<vector<double>> topL = clip(bord, M3, M4);
        vector<vector<double>> leftL = clip(bord, M4, M1);
        drawLine(bottomL);
        drawLine(rightL);
        drawLine(topL);
        drawLine(leftL);
        h += d;
        w += d;
        pAngle = int(pAngle + dAngle) % 360;
    }
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}