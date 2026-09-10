#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>

#define FAILED_GLFW_INITIALIZATION 1
#define FAILED_WINDOW_CREATION 2

const int   initialize(GLFWwindow* window);

void        errorCallback(int error, const char* description);

GLFWwindow* createWindowPointer(const int   width  = 640,
                                const int   height = 480,
                                const char* title  = "Hawk");

void        setOpenglRequirements();

void        cleanup();

void        makeContextCurrent(GLFWwindow* window);

void        run(GLFWwindow* window);

#endif  // WINDOW_H_
