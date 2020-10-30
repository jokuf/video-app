#include <stdio.h>
#include "VideoApp.h"


int main(int argc, const char** argv)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Couldn`t init GLFW\n");
		
		return 1;
	}

	
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	glfwSetWindowSizeLimits(window, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);

	if (!window) {
		printf("Couldn`t open window\n");
		
		glfwTerminate();

		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowCloseCallback(window, windows_close_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwWaitEvents();
	}


	glfwTerminate();

	return 0;
}