#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <window.hpp>

int main() {
  const GLFWwindow* window = create_window();
  initialize(window);
  glfw_cleanup();
  return 0;
}
