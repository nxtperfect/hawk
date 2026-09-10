#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/gl.h>
#include <window.h>

void cleanup() { glfwTerminate(); }

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

const GLFWwindow *create_window(const int width, const int height,
                                const char *title) {
    // Set required version to opengl 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    const GLFWwindow *window =
        glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        // return FAILED_WINDOW_CREATION;
        // TODO how to handle errors
        // should they be handled in-callee or in-caller
        return window;
    }
    return window;
}

const int initialize(GLFWwindow *window) {
    if (!glfwInit()) {
        return FAILED_GLFW_INITIALIZATION;
    }
    glfwSetErrorCallback(error_callback);

    return 0;
}
