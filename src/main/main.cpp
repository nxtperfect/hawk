#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <window.hpp>

int main() {
  GLFWwindow* window = createWindow();
  initializeCallbacks(window);
  cleanup();
  return 0;
}
