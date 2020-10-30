#include <stdio.h>
#include "VideoApp.h"


int main(int argc, const char** argv)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Couldn`t init GLFW\n");
		
		return 1;
	}

	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);

	glfwSetWindowSizeLimits(window, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

	if (!window) {
		printf("Couldn`t open window\n");
		
		glfwTerminate();

		return 1;
	}

	unsigned char* data = new unsigned char[100 * 100 * 3];

	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			data[y * 100 * 3 + x * 3	] = 0xff;
			data[y * 100 * 3 + x * 3 + 1] = 0x00;
			data[y * 100 * 3 + x * 3 + 2] = 0x00;
		}
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowCloseCallback(window, windows_close_callback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();
	}


	glfwTerminate();

	return 0;
}