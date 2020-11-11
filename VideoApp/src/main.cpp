#include <stdio.h>
#include "VideoApp.h"

int main(int argc, const char** argv)
{
	int success;
	char infoLog[512];

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

	// tell OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window.
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetWindowCloseCallback(window, windows_close_callback);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vertexShader = create_vertex_shader(vertices);

	if (!vertexShader) {

		printf("Error: Vertex shader compilation failed.\n");
		glfwTerminate();

		return 1;
	}

	
	unsigned int fragmentShader = create_fragment_shader();

	if (1 > fragmentShader) {
		glfwTerminate();
		glDeleteShader(vertexShader);

		return 1;
	}
	
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

		printf("Error: Unable to link shader program.\n");
		printf("%s\n", infoLog);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glfwTerminate();

		return 1;
	}

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 0, 1);

		glUseProgram(shaderProgram);
		glBindVertexArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();

	return 0;
}
