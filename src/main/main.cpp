#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <window.h>

int main() {
    const GLFWwindow *window = create_window();
    initialize(window);
    cleanup();
    return 0;
}
