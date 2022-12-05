#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "render3d", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glClearColor( 0.f, 0.f, 0.f, 0.f);
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
