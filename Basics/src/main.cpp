#include <string>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include "utils.hpp"
#include "ShaderLoader.hpp"


int main()
{

    // GLFW setup
    if(glfwInit() != GLFW_TRUE)
    {
        fmt::print(fg(fmt::color::red), "Initializing GLFW failed!\n");
        return -1;
    }

    // window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window { glfwCreateWindow(800, 600, "Learning OpenGL!", NULL, NULL) };

    glfwMakeContextCurrent(window);

    // GLEW sutup
    if (glewInit() != GLEW_OK)
    {
        fmt::print(fg(fmt::color::red), "Initializing GLEW failed!\n");
        glfwTerminate();
        return -1;
    }

    initLog();

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, windowFramebufferSizeCallback);


    // ==================== shaders setup ==========================

    GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER) };
    std::string vertexShaderData { ShaderLoader::loadShader(std::filesystem::current_path() / "shaders" / "triangleVertex.glsl") };
    const char* vertexShader_src {vertexShaderData.c_str()};
    glShaderSource(vertexShader, 1, &vertexShader_src, NULL);
    glCompileShader(vertexShader);

    shaderStatusLogger(vertexShader);

    GLuint fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };
    std::string fragmentShaderData { ShaderLoader::loadShader(std::filesystem::current_path() / "shaders" / "triangleFragment.glsl") };
    const char* fragmentShader_src {fragmentShaderData.c_str()};
    glShaderSource(fragmentShader, 1, &fragmentShader_src, NULL);
    glCompileShader(fragmentShader);

    shaderStatusLogger(fragmentShader);

    // linking shaders
    GLuint program { glCreateProgram() };
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    programStatusLogger(program);

    glDeleteShader(vertexShader);  
    glDeleteShader(fragmentShader); 
    

    float vertices[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // VAO setup 
    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO setup
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex attribute(s)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        proccessInput(window);
        glfwPollEvents();

        glClearColor(0.478f, 0, 0.871f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);  
    }

    glfwTerminate();
    return 0;
}