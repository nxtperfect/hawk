#include "window.hpp"
#include <cstdlib>
// #define GLAD_GL_IMPLEMENTATION
// #include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>

void run(GLFWwindow* window) {
  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
}

static void keyCallback(GLFWwindow* window,
                        int         key,
                        int         scancode,
                        int         action,
                        int         mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const int initialize(GLFWwindow* window) {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    return FAILED_GLFW_INITIALIZATION;
  }

  makeContextCurrent(window);

  glfwSetKeyCallback(window, keyCallback);

  glfwSwapInterval(1);
  return 0;
}

void errorCallback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

void makeContextCurrent(GLFWwindow* window) {
  glfwMakeContextCurrent(window);
  // HACK once glad works use below
  // gladLoadGL(glfwGetProcAddress);
}

/* On window failure returns empty pointer
 * uses default arguments of 640x480 pixels with "Hawk" title
 * requires minimum glfw 3.3 core profile
 */
GLFWwindow* createWindowPointer(const int   width,
                                const int   height,
                                const char* title) {
  setOpenglRequirements();

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    cleanup();
    return nullptr;
  }

  return window;
}

// Set required version to opengl 3.3 with core profile
void setOpenglRequirements() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Run before window exit
void cleanup() {
  glfwTerminate();
}
