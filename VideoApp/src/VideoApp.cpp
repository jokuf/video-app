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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Fig::Fig(float * _vertices, int * _indices, int verticesCount, int indicesCount)
{
	vertices = _vertices;
	indices = _indices;
	Fig::verticesCount = verticesCount;
	Fig::indicesCount = indicesCount;
	printf("[CONSTRUCTOR] Vertices count: %d, Indices count:%d\n", verticesCount, indicesCount);
	VAO = 0;
	VBO = 0;
	EBO = 0;
}


void Fig::Init()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount, vertices, GL_STATIC_DRAW);
	
	if (indicesCount > 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicesCount, indices, GL_STATIC_DRAW);
	}


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	printf("[INIT] Vertices count: %d, Indices count:%d\n", verticesCount, indicesCount);
}

void Fig::Render() 
{
	glBindVertexArray(VAO);
	if (indicesCount > 0) {
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	}

	glBindVertexArray(0);
}

void Fig::Destroy()
{
}