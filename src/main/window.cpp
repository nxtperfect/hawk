#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/gl.h>
#include <window.hpp>

const int initialize(GLFWwindow* window) {
  if (!glfwInit()) {
    return FAILED_GLFW_INITIALIZATION;
  }
  glfwSetErrorCallback(glfw_error_callback);

  return 0;
}

// Print glfw error
void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

// On window failure returns empty pointer
// uses default arguments of 640x480 pixels with "Hawk" title
// requires minimum glfw 3.3 core profile
const GLFWwindow* create_window(const int width, const int height,
                                const char* title) {
  set_minimum_opengl_requirements();
  const GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    // Window or OpenGL context creation failed
    // return FAILED_WINDOW_CREATION;
    // TODO how to handle errors
    // should they be handled in-callee or in-caller
    return window;
  }
  return window;
}

// Set required version to opengl 3.3 with core profile
void set_minimum_opengl_requirements() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Run before window exit
void glfw_cleanup() { glfwTerminate(); }
