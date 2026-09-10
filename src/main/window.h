#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>
#include <cstdio>

#define GLFW_INCLUDE_NONE
#define FAILED_GLFW_INITIALIZATION 1;
#define FAILED_WINDOW_CREATION 2;

void cleanup();

void error_callback(int error, const char *description);

const GLFWwindow *create_window(const int width = 640, const int height = 480,
                                const char *title = "Hawk");

const int initialize(const GLFWwindow *window);

#endif // WINDOW_H_
