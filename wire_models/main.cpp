#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
double pi = M_PI;

void DrawOctahedronSide(float size) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size, 0);
	glVertex3f(size / 2, 0, size / 2);
	glVertex3f(-size / 2, 0, size / 2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -size, 0);
	glVertex3f(size / 2, 0, size / 2);
	glVertex3f(-size / 2, 0, size / 2);
	glEnd();
}

void DrawOctahedron(float size) {
	DrawOctahedronSide(size);
	glRotatef(90, 0, 1, 0);
	DrawOctahedronSide(size);
	glRotatef(90, 0, 1, 0);
	DrawOctahedronSide(size);
	glRotatef(90, 0, 1, 0);
	DrawOctahedronSide(size);
	glRotatef(90, 0, 1, 0);
}

void DrawCubeSide(float size) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
}

void DrawDownSidePyramid(float size) {
	glBegin(GL_POLYGON);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
}

void DrawCube(float size) {
	DrawCubeSide(size);
	glRotatef(90, 0, 1, 0);
	DrawCubeSide(size);
	glRotatef(90, 0, 1, 0);
	DrawCubeSide(size);
	glRotatef(90, 0, 1, 0);
	DrawCubeSide(size);
	glRotatef(90, 0, 1, 0);
	DrawCubeSide(size);
	glRotatef(90, 1, 0, 0);
	DrawCubeSide(size);
	glRotatef(180, 1, 0, 0);
	DrawCubeSide(size);
}

void DrawPyramidSide(float size) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size / 2, 0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
}

void DrawPyramid(float size) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	DrawPyramidSide(size);
	glRotatef(90, 0, 1, 0);
	DrawPyramidSide(size);
	glRotatef(90, 0, 1, 0);
	DrawPyramidSide(size);
	glRotatef(90, 0, 1, 0);
	DrawPyramidSide(size);
	glRotatef(90, 1, 0, 0);
	DrawDownSidePyramid(size);
}

void DrawTetrahedronSide(float size) {
	glLineWidth(1);
	float height = sqrt(size * size - ((size / 2) * (size / 2)));
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, height / 2, 0);
	glVertex3f(size / 2, -height / 2, -height / 3);
	glVertex3f(-size / 2, -height / 2, -height / 3);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -height / 2, 0);
	glVertex3f(size / 2, -height / 2, -height / 3);
	glVertex3f(-size / 2, -height / 2, -height / 3);
	glEnd();
}

void DrawTetrahedron(float size) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DrawTetrahedronSide(size);
	glRotatef(120, 0, 1, 0);
	DrawTetrahedronSide(size);
	glRotatef(120, 0, 1, 0);
	DrawTetrahedronSide(size);
}

void DrawCylinderSide(float height, float radius, int pices) {
	glLineWidth(1);
	double angle = 360 / pices;
	float side = sqrt((radius * radius) + (radius * radius) - (2 * radius * radius * cos(angle * pi / 180)));
	float need = sqrt((radius * radius) - ((side / 2) * (side / 2)));
	glBegin(GL_LINE_LOOP);
	glVertex3f(-side / 2, height / 2, need);
	glVertex3f(side / 2, height / 2, need);
	glVertex3f(side / 2, -height / 2, need);
	glVertex3f(-side / 2, -height / 2, need);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, height / 2, 0);
	glVertex3f(side / 2, height / 2, need);
	glVertex3f(-side / 2, height / 2, need);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -height / 2, 0);
	glVertex3f(side / 2, -height / 2, need);
	glVertex3f(-side / 2, -height / 2, need);
	glEnd();
}

void DrawCylinder(float height, float radius, float pices) {
	int p = pices;
	double angle = 360 / pices;
	while (p > 0) {
		DrawCylinderSide(height, radius, pices);
		glRotatef(angle, 0, 1, 0);
		p--;
	}
}

void DrawConeSide(float height, float radius, float pices) {
	glLineWidth(1);
	double angle = 360 / pices;
	float side = sqrt((radius * radius) + (radius * radius) - (2 * radius * radius * cos(angle * pi / 180)));
	float need = sqrt((radius * radius) - ((side / 2) * (side / 2)));

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, height / 2, 0);
	glVertex3f(side / 2, -height / 2, need);
	glVertex3f(-side / 2, -height / 2, need);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -height / 2, 0);
	glVertex3f(side / 2, -height / 2, need);
	glVertex3f(-side / 2, -height / 2, need);
	glEnd();
}

void DrawCone(float height, float radius, float pices) {
	int p = pices;
	double angle = 360 / pices;
	while (p > 0) {
		DrawConeSide(height, radius, pices);
		glRotatef(angle, 0, 1, 0);
		p--;
	}
}

int current = 0;
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
        current = current < 5 ? ++current : 0;
}

int main(void) {

	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(800, 800, "", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glColor3f(0.4, 0.4, 0.4);
		glLineWidth(1);

		glPushMatrix();

		glfwSetKeyCallback(window, key_callback);
        switch (current)
        {
        case 0:
            DrawCube(0.6);
            break;
        case 1:
            DrawCylinder(0.8, 0.4, 10);
            break;
        case 2:
            DrawPyramid(0.7);
            break;
        case 3:
            DrawCone(0.8, 0.4, 10);
            break;
        case 4:
            DrawTetrahedron(0.90);
            break;
        case 5:
            DrawOctahedron(0.87);
            break;
        default:
            break;
        }
		// DrawCube(0.6);
		// DrawCylinder(0.8, 0.4, 10);
		// DrawPyramid(0.7);
		// DrawCone(0.8, 0.4, 10);
		// DrawTetrahedron(0.90);
		// DrawOctahedron(0.87);

		glPopMatrix();
		glRotatef(-0.2, 0.8, 0.6, 0.3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
