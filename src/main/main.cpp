#include <GLFW/glfw3.h>
#include "window.hpp"

int main() {
  const GLFWwindow* window = createWindowPointer();
  initialize(window);
  cleanup();
  return 0;
}
