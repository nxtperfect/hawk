#pragma once

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum class InitResult {
  SUCCESS,
  GLFW_INITIALIZATION_FAILED,
  WINDOW_CREATION_FAILED
};

InitResult  initializeCallbacks(GLFWwindow* window);

void        setBufferSwapInterval(const int interval = 1);

GLFWwindow* createWindow(const int   width  = 640,
                         const int   height = 480,
                         const char* title  = "Hawk");

void        setOpenGLRequirements();

void        cleanup();

void        makeContextCurrent(GLFWwindow* window);

void        run(GLFWwindow* window);
