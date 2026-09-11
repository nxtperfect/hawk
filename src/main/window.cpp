#include <cstdlib>
#include <window.hpp>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>

void run(GLFWwindow* window) {
  setBufferSwapInterval();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapBuffers(window);
  }
}

static void keyCallback(GLFWwindow* window,
                        int         key,
                        int         scancode,
                        int         action,
                        int         mods) {
  (void)scancode;
  (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void errorCallback(int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

InitResult initializeCallbacks(GLFWwindow* window) {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    return InitResult::GLFW_INITIALIZATION_FAILED;
  }

  makeContextCurrent(window);

  glfwSetKeyCallback(window, keyCallback);

  return InitResult::SUCCESS;
}

void setBufferSwapInterval(const int interval) {
  glfwSwapInterval(interval);
}

void makeContextCurrent(GLFWwindow* window) {
  glfwMakeContextCurrent(window);
  // HACK once glad works use below
  // gladLoadGL(glfwGetProcAddress);
}

/* On window failure returns empty pointer
 * uses default arguments of 640x480 with "Hawk" title
 * requires opengl 4.6 core profile
 */
GLFWwindow* createWindow(const int width, const int height, const char* title) {
  setOpenGLRequirements();

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    cleanup();
    return nullptr;
  }

  return window;
}

// Set required version to opengl 4.6 with core profile
void setOpenGLRequirements() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Run before window exit
void cleanup() {
  glfwTerminate();
}
