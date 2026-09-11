#pragma once

#include <GLFW/glfw3.h>

enum class InitError {
  NONE,
  GLFW_INITIALIZATION_FAILED,
  WINDOW_CREATION_FAILED,
  CONTEXT_CREATION_FAILED
};

struct InitResult {
  GLFWwindow* window;
  InitError   error;
};

InitResult  initialize();

void        initializeCallbacks(GLFWwindow* window);

void        setBufferSwapInterval(const int interval = 1);

GLFWwindow* createWindow(const int   width  = 640,
                         const int   height = 480,
                         const char* title  = "Hawk");

void        setOpenGLRequirements();

void        cleanup();

bool        makeContextCurrent(GLFWwindow* window);

void        run(GLFWwindow* window);
