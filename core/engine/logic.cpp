#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../entities/triangle.h"
#include <functional>

GLFWwindow* window;


GLuint vertexShader;
GLuint fragmentShader;
GLuint shader_program;

int w_width = 800;
int w_height = 600;

float _x = 0;

Engine _engine;

/***************************************************************************************/

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int InitGlfw()
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

int InitWindow(int width, int height, const char name[])
{
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    return 0;
}

int Close()
{
    return glfwWindowShouldClose(window);
}

void InitOpengl()
{
    glfwGetFramebufferSize(window, &w_width, &w_height);
    glViewport(0, 0, w_width, w_height);
}

void UpdateScreen()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void QuitOpengl()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InitObjects(const std::function<void()>& InitCode)
{
    InitCode();
    _engine.Update();
}

void Update(const std::function<void()>& LoopFunction)
{
    while (!Close()) 
    {
        ClearScreen();
        LoopFunction(); // MainLoop()
        UpdateScreen();
    }
}