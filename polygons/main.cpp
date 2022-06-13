#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {

	srand(time(NULL));

	GLFWwindow* window;

	//initialize the lib

	if (!glfwInit()) {
		return -1;
	}

	// create window mode
	window = glfwCreateWindow(800, 600, "", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// make the window's context current
	glfwMakeContextCurrent(window);

#define RANDOM (2*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1.0)

const int N = 4;

#define VERTEX_X 0
#define VERTEX_Y 1
	float arr[N][2];
	for (int i = 0; i < N; i++) {
		arr[i][VERTEX_X] = RANDOM;
		arr[i][VERTEX_Y] = RANDOM;
	}

	// loop until user close window
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the OpenGl
		glLoadIdentity();

		glColor3f(0.3, 0.7, 0.6);
		glBegin(GL_POLYGON);
		for (int i = 0; i < N; i++) {
			glVertex2f(arr[i][VERTEX_X], arr[i][VERTEX_Y]);
		}
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < N; i++) {
			glVertex2f(arr[i][VERTEX_X], arr[i][VERTEX_Y]);
		}
		glEnd();

		// swap front and back buffers
		glfwSwapBuffers(window);

		// poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}