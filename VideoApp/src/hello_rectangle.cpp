#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VideoApp.h"
#include "Shader.h"

#if defined(_MSC_VER)
#include <direct.h>
#define getcwd _getcwd
#elif defined(__GNUC__)
#include <unistd.h>
#endif

char* file_open(char* path);

int main(int argc, char** argv)
{
	printf("Hello world\n");


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello triangle", NULL, NULL);

	if (window == NULL) {
		printf("Failed to create window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");

		return -1;
	}

	glViewport(0, 0, 800, 600);
	
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shaderProgram("./resources/shaders/vertex/default.vs", "./resources/shaders/fragment/default.fs");


	float vertices[] = {
		-0.5f, 0.6f, 0.0f,
		-0.7f, 0.3f, 0.0f,
		-0.3f, 0.3f, 0.0f
	};

	Fig triangle(shaderProgram, vertices, (int*)0, sizeof(vertices) / sizeof(float), 0);

	triangle.Init();

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shaderProgram.use();
	float xOffset = 0;
	double nextTime = glfwGetTime() + 1;
	
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetTime() >= nextTime) {
			nextTime += 1;
			xOffset += 0.1f;
			
			shaderProgram.setFloat("xOffset", xOffset);
		}
		else {
			//shaderProgram.setFloat("xOffset", 0);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		triangle.Render();
	}

	glfwTerminate();

	return 0;
}
