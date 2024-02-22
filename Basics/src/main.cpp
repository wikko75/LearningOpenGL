#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <filesystem>
#include <chrono>
#include <random>
#include "utils.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"


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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // ==================== shader setup ==========================
    
    Shader trianglesShader { std::filesystem::current_path() / "shaders" / "triangleVertex.glsl",
                             std::filesystem::current_path() / "shaders" / "triangleFragment.glsl" };


    float upperTrianglesData[] = {
        
        -0.5f, -0.5f, 0.0f,           // bottom left
        0.98f, 0.804f, 0.106f, 1.0f,  // yellow
        0.0f, 0.0f,                   // tex coord
        
        0.5f, -0.5f, 0.0f,            // bottom right
        0.976f, 0.109f, 0.043f, 0.5f, // red
        1.f, 0.0f,                    // tex coord

        -0.5f,  0.5f, 0.0f,           // upper left
        0.603f, 1.0f, 0.101f, 1.0f,   // green
        0.f, 1.0f,                    // tex coord

        0.5f, 0.5f, 0.0f,             // upper right
        0.046f, 0.109f, 0.976f, 0.5f, // blue
        1.f, 1.0f,                    // tex coord
    };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
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

    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    GLuint EBO {};
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    Texture scottTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "textures" / "scott.jpg", 0, GL_RGB };

    scottTexture.setWrapMethod(GL_REPEAT, GL_REPEAT);
    scottTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    scottTexture.createTexture();

    Texture wallTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "textures" / "wall.jpg", 0, GL_RGB };

    wallTexture.setWrapMethod(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    wallTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    wallTexture.createTexture();



    // ------- texture units setup --------
    trianglesShader.useShader();
    glUniform1i(glGetUniformLocation(trianglesShader.getProgram(), "inTexture0"), 0);
    glUniform1i(glGetUniformLocation(trianglesShader.getProgram(), "inTexture1"), 1);


    // ------- config stuff --------
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
    std::random_device rd{};
    std::mt19937 mt { rd() };
    std::uniform_real_distribution u_rel_num { 0.f, 1.f };
    float randomAngle { u_rel_num(mt) * 80 };

    float lastFrame {};
    float deltaTime {};
    

    // ------- camera setup --------
    Camera camera { window,  800, 600, 0.f, -90.f, 0.05f, 3.5f, glm::vec3{ 0.0f, 0.f, 4.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f } };


    while (!glfwWindowShouldClose(window))
    {
        proccessInput(window);
        glfwPollEvents();

        float time { static_cast<float>(glfwGetTime()) };
        deltaTime = time - lastFrame;
        lastFrame = time;
        
        // ------- background color -------
        float redVal    { cos(time * 0.5f) / 2.f + 0.6f};
        float greenVal  { sin(time * 0.7f) / 2.0f + 0.6f };
        float blueVal   { sin(time) / 2.f + 0.6f };

        glClearColor(redVal, greenVal, blueVal, 0.761f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        trianglesShader.useShader();

        GLint vertexColorLoc { glGetUniformLocation(trianglesShader.getProgram(), "color") };
        glUniform4f(vertexColorLoc, redVal, greenVal, blueVal, 1.0f);

        // ------- textures setup -------
        glActiveTexture(GL_TEXTURE0);
        scottTexture.bindTexture();

        glActiveTexture(GL_TEXTURE1);
        wallTexture.bindTexture();


        camera.updatePosition(deltaTime);
        camera.cameraLog();

        // -------- cubes trans. and drawing --------
        glBindVertexArray(VAO);
        for (int i {0}; i < sizeof(cubePositions) / (cubePositions->length() * sizeof(float)); ++i)
        {
            glm::mat4 trans { 1.0f };
            glm::mat4 view { glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getDirection(), { 0.0f, 1.0f, 0.0f }) };
            trans = glm::perspective(glm::radians(45.f), 4 / (float)3, 0.1f, 100.f);    // projection
            trans = trans * view;     // view
            trans = glm::translate(trans, cubePositions[i]);    // model
            trans = glm::rotate(trans, time * glm::radians(randomAngle * i + 10.f),  glm::vec3(1.0f, 0.3f, 0.5f));   // model
            // trans = glm::scale(trans, { abs(sin(time)), abs(sin(time)),  abs(sin(time)) }); //model
            
            glUniformMatrix4fv(glGetUniformLocation(trianglesShader.getProgram(), "transformMtx"), 1, GL_FALSE, glm::value_ptr(trans));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);  
    }


    // cleanup
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return 0;
}