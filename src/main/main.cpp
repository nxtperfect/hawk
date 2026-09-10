#include <cstdio>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#define FAILED_GLFW_INITIALIZATION 1;
#define FAILED_WINDOW_CREATION 2;

void cleanup() { glfwTerminate(); }

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow create_window(int width = 640, int height = 480,
                         const char *title = "Hawk") {
    // Set required version to opengl 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        return FAILED_WINDOW_CREATION;
    }
    return *window;
}

int initialize() {
    if (!glfwInit()) {
        return FAILED_GLFW_INITIALIZATION;
    }
    GLFWwindow *window = create_window();
    glfwSetErrorCallback(error_callback);

    return 0;
}

int main() {
    initialize();
    cleanup();
    return 0;
}
