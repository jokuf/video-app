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

	Shader shaderProgram("./shaders/vertex/default.vs", "./shaders/fragment/default.fs");

	shaderProgram.use();

	float roofVertices[] = { 
		0.3f, 0.7f, 0.0f, 
		0.0f, 0.4f, 0.0f,
		0.5f, 0.4f, 0.0f
	};

	float roof_vertices2[] = {
		0.8f, 0.7f, 0.0f,
		0.3f, 0.7f, 0.0f,
		0.5f, 0.4f, 0.0f,
		1.0f, 0.4f, 0.0f
	};
	
	int roof_indices[] = {
		0,3,2,
		3,1,0
	};

	float house_vertices[] = {
		0.4f, 0.4f, 0.0f, // 0 -> top right
		0.1f, 0.4f, 0.0f, // 1 -> top left
		0.1f, 0.1f, 0.0f, // 2 -> bottom left
		0.4f, 0.1f, 0.0f, // 3 -> bottom right
		0.9f, 0.4f, 0.0f, // 4 -> right right top
		0.9f, 0.1f, 0.0f, // 5 -> right right down
	};

	int house_indices[] = {
		5, 3, 4,
		4, 0, 3,
		3, 2, 0,
		0, 1, 2
	};

	Fig roofFront(roofVertices, (int*)0, 9, 0);
	Fig roofSecond(roof_vertices2, roof_indices, sizeof(roof_vertices2) / sizeof(float), sizeof(roof_indices) / sizeof(int));
	Fig house(house_vertices, house_indices, 18, 12);
	
	house.Init();
	roofSecond.Init();
	roofFront.Init();

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		roofFront.Render();
		roofSecond.Render();
		house.Render();
	}


	glfwTerminate();

	return 0;
}
