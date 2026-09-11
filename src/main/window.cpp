#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <window.hpp>

typedef struct Vertex {
  vec2 pos;
  vec3 col;
} Vertex;

static const Vertex vertices[3] = {
    {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
    { {0.6f, -0.4f}, {0.f, 1.f, 0.f}},
    {   {0.f, 0.6f}, {0.f, 0.f, 1.f}}
};

static const char* vertex_shader_text =
    "#version 330\n"
    "uniform mat4 MVP;\n"
    "in vec3 vCol;\n"
    "in vec2 vPos;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

static const char* fragment_shader_text =
    "#version 330\n"
    "in vec3 color;\n"
    "out vec4 fragment;\n"
    "void main()\n"
    "{\n"
    "    fragment = vec4(color, 1.0);\n"
    "}\n";

void run(GLFWwindow* window) {
  setBufferSwapInterval();
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  const GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  const GLint mvp_location  = glGetUniformLocation(program, "MVP");
  const GLint vpos_location = glGetAttribLocation(program, "vPos");
  const GLint vcol_location = glGetAttribLocation(program, "vCol");

  GLuint      vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, col));

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  cleanup();
  exit(EXIT_SUCCESS);
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

InitResult initialize() {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    cleanup();
    return {nullptr, InitError::GLFW_INITIALIZATION_FAILED};
  }

  GLFWwindow* window = createWindow();

  if (!window) {
    cleanup();
    return {nullptr, InitError::WINDOW_CREATION_FAILED};
  }

  glfwSetKeyCallback(window, keyCallback);

  if (!makeContextCurrent(window)) {
    cleanup();
    return {nullptr, InitError::CONTEXT_CREATION_FAILED};
  }

  // TODO this ends up being bad
  // need to make this function
  // either not create a window
  // or return that + the code
  // funnily enough that becomes
  // <Value,Error> from rust :3
  return {window, InitError::NONE};
}

void setBufferSwapInterval(const int interval) {
  glfwSwapInterval(interval);
}

bool makeContextCurrent(GLFWwindow* window) {
  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return false;
  }
  return true;
}

/* On window failure returns empty pointer
 * uses default arguments of 640x480 with "Hawk" title
 * requires opengl 3.2 core profile
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

// Set required version to opengl 3.2 with core profile
void setOpenGLRequirements() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Run before window exit
void cleanup() {
  glfwTerminate();
}
