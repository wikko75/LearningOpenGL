#include <string>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include "utils.hpp"
#include "Shader.hpp"


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



    // ==================== shader setup ==========================

    Shader trianglesShader { std::filesystem::current_path() / "shaders" / "triangleVertex.glsl",
                             std::filesystem::current_path() / "shaders" / "triangleFragment.glsl" };


    float upperTrianglesData[] = {
        -0.75f, 0.25f, 0.0f,
        0.98f, 0.804f, 0.106f, 1.0f,  // yellow
        -0.25f, 0.25f, 0.0f,
        0.976f, 0.109f, 0.043f, 0.5f, // red
        -0.5f,  0.75f, 0.0f,
        0.603f, 1.0f, 0.101f, 1.0f,   // green

        0.25f, 0.25f, 0.0f,
        0.976f, 0.109f, 0.043f, 0.5f, // red
        0.75f, 0.25f, 0.0f,
        0.98f, 0.804f, 0.106f, 1.0f,  // yellow
        0.5f,  0.75f, 0.0f,
        0.603f, 1.0f, 0.101f, 1.0f,   // green
    };

    float lowerTrianglesData[] = {
        -0.25f, -0.25f, 0.0f,
        1.0f, 0.5f, 1.0f, 0.5f,  // color
        0.25f, -0.25f, 0.0f,
        1.0f, 1.0f, 0.5f, 0.5f,  // color
        0.0f, -0.75f, 0.0f,
        0.5f, 1.0f, 1.0f, 0.5f   // color
    };

    // VAO setup 
    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO setup
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(upperTrianglesData), upperTrianglesData, GL_STATIC_DRAW);

    // vertex attribute(s)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint indices[] = {
        0, 4, 2,
        2, 4, 5
    };

    GLuint EBO {};
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint VAO_2 {};
    glCreateVertexArrays(1, &VAO_2);
    glBindVertexArray(VAO_2);

    GLuint VBO_2 {};
    glGenBuffers(1, &VBO_2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lowerTrianglesData), lowerTrianglesData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        proccessInput(window);
        glfwPollEvents();

        glClearColor(0.478f, 0, 0.871f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        trianglesShader.useShader();

        // ---- uncomment for color changing (change in frag shader required):) ------
        float time { static_cast<float>(glfwGetTime()) };
        float greenVal { sin(time * 0.7f) / 2.0f + 0.6f };
        float redVal { cos(time * 0.5f) / 2.f + 0.6f};
        float blueVal { sin(time) / 2.f + 0.6f };
        GLint vertexColorLoc { glGetUniformLocation(trianglesShader.getProgram(), "color") };
        glUniform4f(vertexColorLoc, redVal, greenVal, blueVal, 1.0f);
        
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO_2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);  
    }


    // cleanup
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBO_2);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAO_2);

    glfwTerminate();
    return 0;
}