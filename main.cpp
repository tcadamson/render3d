#include "render3d/shader.h"

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// https://github.com/nothings/stb/blob/master/stb_image.h#L4
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main()
{
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;
    // GLFW + OpenGL initial setup operations
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "render3d", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to initialize GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (mode->width - WINDOW_WIDTH) / 2, (mode->height - WINDOW_HEIGHT) / 2); // Center window on primary monitor
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    Shader shader("default");

    // Cube rendering segment
    // Cube vertices courtesy of https://learnopengl.com/code_viewer.php?code=getting-started/cube_vertices
    const float cubeVertices[]
    {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
    unsigned int vbo;
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // Vertex (2 attributes): 12 position bytes + 8 texel bytes
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // Texel attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture loading segment via stbi_image.h
    int textureWidth;
    int textureHeight;
    int textureChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *textureData = stbi_load("render3d/textures/cube.png", &textureWidth, &textureHeight, &textureChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture loading failed." << std::endl;
    }
    stbi_image_free(textureData);

    while (!glfwWindowShouldClose(window))
    {
        // Background clear color (pure white)
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Cube rendering math
        const float orbitRadius = 4.0f;
        const float orbitSpeed = 40.0f;
        const float orbitBodyScale = 0.75f;
        const float spinSpeed = 40.0f;
        int combinationLocation = glGetUniformLocation(shader.programID, "combination");
        glm::vec3 spinAxis(1.0f, 0.5f, 0.3f);
        glm::vec3 orbitAxis(0.0f, 1.0f, 0.0f);
        glm::mat4 model(1.0f);
        glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f)));
        glm::mat4 projection(glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.0f));
        model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(spinSpeed), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(combinationLocation, 1, GL_FALSE, glm::value_ptr(projection * view * model));
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vao);
        shader.useProgram();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glm::mat4 spin(glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()) * glm::radians(spinSpeed), spinAxis));
        model = glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()) * glm::radians(orbitSpeed), orbitAxis);
        model = glm::scale(model, glm::vec3(orbitBodyScale));
        model = glm::translate(model, glm::vec3(-orbitRadius, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(orbitSpeed), orbitAxis);
        model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));
        glUniformMatrix4fv(combinationLocation, 1, GL_FALSE, glm::value_ptr(projection * view * model * spin));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // GLFW post-frame operations
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW + OpenGL cleanup operations
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();

    return 0;
}
