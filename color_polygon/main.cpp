#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(800, 600, "", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glLoadIdentity();

		glLineWidth(3);
		glColor3f(8.0, 1.0, 1.0);

		glBegin(GL_TRIANGLES);

        float p1 = 0.1;
        float p2 = 0.25;
        float p3 = 0.4;
        float p5 = 0.88;
        float p6 = 0.56;
        float p7 = 0.79;
        float p8 = 0.15;
        float p9 = 0.7;
        float p11 = 0.82;
        float p12 = 0.4;

        glColor3f(0.8, 0.5, 0.3);
		glVertex2f(p1, p1);
		glVertex2f(p5, p2);
		glVertex2f(-p6, p3);

		glColor3f(0.2, 0.4, 0.1);
		glVertex2f(p1, -p7);
		glVertex2f(p1, p1);
		glVertex2f(p5, p2);

		glColor3f(0.7, 0.4, 0.9);
		glVertex2f(p1, p1);
		glVertex2f(-p5, -p11);
		glVertex2f(-p7, p8);

		glColor3f(0.1, 0.9, 0.6);
		glVertex2f(-p6, p3);
		glVertex2f(-p7, p8);
		glVertex2f(p1, p1);

		glEnd();
		glPopMatrix();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
