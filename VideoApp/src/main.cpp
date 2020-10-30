#include <stdio.h>
#include "VideoApp.h"


int main(int argc, const char** argv)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Couldn`t init GLFW\n");
		
		return 1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeLimits(window, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize OpenGL context\n");
		glfwTerminate();

		return -1;
	}
	

	// Define the viewport dimensions
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	unsigned char* data = new unsigned char[100 * 100 * 3];

	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			data[y * 100 * 3 + x * 3	] = 0xff;
			data[y * 100 * 3 + x * 3 + 1] = 0x00;
			data[y * 100 * 3 + x * 3 + 2] = 0x00;
		}
	}

	for (int y = 25; y < 75; y++) {
		for (int x = 25; x < 75; x++) {
			data[y * 100 * 3 + x * 3	] = 0x00;
			data[y * 100 * 3 + x * 3 + 1] = 0x00;
			data[y * 100 * 3 + x * 3 + 2] = 0xff;
		}
	}
	
	glfwSetWindowCloseCallback(window, windows_close_callback);

	while (!glfwWindowShouldClose(window)) {
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
	
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}