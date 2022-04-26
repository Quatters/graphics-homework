#include <iostream>
#include "GL/glut.h"

const int WIDTH = 800;
const int HEIGHT = 800;

float spin = 0.0f;

float a = 0.00f;
float b = 0.01f;
float c = 0.01f;
float d = 0.00f;

void draw_line(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

float f(float x) {
    return a * (x * x * x) + b * (x * x) + c * x + d;
}

void display() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float w = WIDTH;
    float h = HEIGHT;

    float x_center = w / 2.0f;
    float y_center = h / 2.0f;

    glColor3f(0.8f, 0.8f, 0.8f);
    draw_line(0, y_center, w, y_center);
    draw_line(x_center, 0, x_center, h);

    float step = 0.05f;

    glBegin(GL_LINE_STRIP);

    glColor3f(0, 0, 0);

    float x = 0;
    while (x <= w + step) {
        float y = f(x - x_center) + y_center;
        glVertex2f(x, y);
        x += step;
    }

    glEnd();

    glFinish();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void show_equation() {
    std::system("clear");
    std::cout << "f(x) = " << a << "x^3 + " << b << "x^2 + " << c << "x + " << d << std::endl;
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') a += 0.01f;
    else if (key == '2') a -= 0.01f;
    else if (key == '3') b += 0.01f;
    else if (key == '4') b -= 0.01f;
    else if (key == '5') c += 0.01f;
    else if (key == '6') c -= 0.01f;
    else if (key == '7') d += 0.01f;
    else if (key == '8') d -= 0.01f;
    show_equation();

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("");
    show_equation();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
