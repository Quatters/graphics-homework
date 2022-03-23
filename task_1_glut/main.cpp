#include <iostream>
#include <math.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#define SPACEBAR 32

double angle = M_PI / 2;

void renderScene() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5);

    glBegin(GL_LINES);
    glVertex2d(cos(angle) * 0.75, sin(angle) * 0.75);
    glVertex2d(0, 0);  
    glEnd();

    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y) {
    if (key == SPACEBAR) {
        angle = (double)rand();
    }
}

int main(int argc, char** argv) {
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("some window");

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(handleKeyboard);

    glutMainLoop();

    return 1;
}
