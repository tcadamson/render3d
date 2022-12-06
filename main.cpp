#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int OPENGL_VERSION_MAJOR = 3;
const int OPENGL_VERSION_MINOR = 3;

void framebufferSizeCallback(GLFWwindow */*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int compileShader(int shaderType, const char *shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
    int success;
    int logLength;
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (!success)
    {
        char log[logLength];
        glGetShaderInfoLog(shader, logLength, nullptr, log);
        std::cout << "Shader " << shaderType << " compilation failed\n" << log << std::endl;
    }
    return shader;
}

unsigned int createShaderProgram(const std::vector<unsigned int> &shaders)
{
    unsigned int shaderProgram = glCreateProgram();
    for (unsigned int shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    for (unsigned int shader : shaders)
    {
        glDeleteShader(shader);
    }
    return shaderProgram;
}

int main()
{
    // GLFW initialization and window setup (supports OpenGL >= 3.3)
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "render3d", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width - WINDOW_WIDTH) / 2, (mode->height - WINDOW_HEIGHT) / 2); // Center window on primary monitor
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwMakeContextCurrent(window);

    // GLAD initialization (must be called before any OpenGL function)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Triangle render test
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.f);\n"
        "}\0";
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.f, 1.f, 1.f, 1.f);\n"
        "}\0";
    std::vector<unsigned int> shaders = {
        compileShader(GL_VERTEX_SHADER, vertexShaderSource),
        compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource)
    };
    unsigned int vao;
    unsigned int vbo;
    unsigned int shaderProgram = createShaderProgram(shaders);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
    glEnableVertexAttribArray(0); // 0 is the vertex attribute location as defined in vertex shader

    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up OpenGL and GLFW resources
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
