#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int error = 0;
    int dErr = dy + 1;
    int y = y1;
    int dirY = y2 - y1;
    if (dirY > 0)
        dirY = 1;
    else if (dirY < 0)
        dirY = -1;

    for (int x = x1; x <= x2; x++) {
        setPixel(x, y);
        error += dErr;
        if (error >= dx + 1) {
            y += dirY;
            error -= dx + 1;
        }
    }
}

void drawCircle(int x0, int y0, int r) {
    int x = 0;
    int y = r;
    int delta = 1 - 2 * r;
    int error = 0;

    while (y >= x) {
        setPixel(x0 + x, y0 + y);
        setPixel(x0 + x, y0 - y);
        setPixel(x0 - x, y0 + y);
        setPixel(x0 - x, y0 - y);
        setPixel(x0 + y, y0 + x);
        setPixel(x0 + y, y0 - x);
        setPixel(x0 - y, y0 + x);
        setPixel(x0 - y, y0 - x);

        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0) {
            delta += 2 * ++x + 1;
            continue;
        }
        if (delta > 0 && error > 0) {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }
}

void renderScene() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 500.0, 0.0);

    glColor3f(0, 0, 0);

    drawLine(10, 41, 97, 10);

    drawCircle(250, 250, 50);
    drawCircle(250, 250, 137);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("some window");

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 1;
}
