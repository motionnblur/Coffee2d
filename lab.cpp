#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "core/entities/triangle.h"
#include "./lib/reader.cpp"
#ifndef ENGINE_H
#define ENGINE_H
#endif
#include <functional>

GLFWwindow* window;

GLuint VBO;
GLuint VAO;
GLuint EBO;

GLuint vertexShader;
GLuint fragmentShader;
GLuint shader_program;

int w_width = 800;
int w_height = 600;

float _x = 0;

Engine _engine;

Triangle triangle(_engine);
Triangle triangle2(_engine);

/***************************************************************************************/

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void InitEngine()
{
    //_engine = new Engine;
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
    triangle.Init(_engine);

    triangle.InitShaders(ReadFile("shaders/vert.shader"), ReadFile("shaders/frag.shader"), 
        vertexShader, fragmentShader, shader_program);

    triangle.SetSize(0.1);
    triangle.SetPos(0.0, 0.0);

    triangle.SendTriangleDataToEngine(VBO, VAO);

    triangle2.Init(_engine);

    triangle2.InitShaders(ReadFile("shaders/vert.shader"), ReadFile("shaders/frag.shader"), 
        vertexShader, fragmentShader, shader_program);

    triangle2.SetSize(0.1);
    triangle2.SetPos(0.5, 0.0);

    triangle2.SendTriangleDataToEngine(VBO, VAO);

    _engine.Update(VBO, VAO);

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

void Update(const std::function<void()>& LoopFunction)
{
    while (!Close()) 
    {
        ClearScreen();
        LoopFunction(); // MainLoop()
        UpdateScreen();
    }
}

void MainLoop()
{
    Update([](){
        //triangle.UpdatePos(0.0002, 0.0001, shader_program, VAO);
        triangle2.UpdatePos(-0.0002, 0.0, shader_program, VAO);
    });
}