#include <stdio.h>
#include "VideoApp.h"


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


void windows_close_callback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);

	printf("[Event] Close window\n");
}
