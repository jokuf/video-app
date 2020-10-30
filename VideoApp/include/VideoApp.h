#pragma once

/**
  * Be sure to include GLAD before GLFW. The include file for GLAD includes the requiredOpenGL headers behind the scenes (likeGL/gl.h) 
  * so be sure to include GLAD beforeother header files that require OpenGL (like GLFW).
  */
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#ifndef VIDEOAPP_H
#define VIDEOAPP_H

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 640
#endif // !WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 480
#endif // !1


void error_callback(int error, const char* description);
void windows_close_callback(GLFWwindow* window);

#endif // !VIDEO_APP_H
