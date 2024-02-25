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
    
    Shader cubeShader { std::filesystem::current_path() / "shaders" / "cubeVertex.glsl",
                        std::filesystem::current_path() / "shaders" / "cubeFragment.glsl" };


    Shader floorShader { std::filesystem::current_path() / "shaders" / "floorVertex.glsl",
                         std::filesystem::current_path() / "shaders" / "floorFragment.glsl" };


    Shader coolPyramidShader { std::filesystem::current_path() / "shaders" / "coolPyramidVertex.glsl",
                               std::filesystem::current_path() / "shaders" / "coolPyramidFragment.glsl" };



    // =================== verticies data =========================

    float coolPyramidVertices[] = {
        -0.5f, 0.f, 0.5f,             // front left
        0.976f, 0.109f, 0.043f, 0.5f, // red
        
        0.5f, 0.f, 0.5f,               // front right
        0.603f, 1.0f, 0.101f, 1.0f,   // green

        0.f,  0.8f, 0.0f,             // middle
        0.046f, 0.109f, 0.976f, 0.5f, // blue

        -0.5f, 0.f, -0.5f,             // back left
        0.98f, 0.804f, 0.106f, 1.0f,  // yellow

        0.5f, 0.0, -0.5f,               // back right
        0.729f, 0.035f, 0.925f, 1.f   // violet
    };

    float cubeVertices[] = {
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

    float floorVerticies[] = {
        -0.5f, -0.5f, -0.2f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.2f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.2f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.2f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.2f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.2f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.2f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.2f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.2f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.2f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.2f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.2f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.2f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.2f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.2f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.2f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.2f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.2f,  0.0f, 1.0f
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



    // ================= VAO / VBO  setup ====================

    GLuint cubeVAO;
    glCreateVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    GLuint cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    GLuint floorVAO;
    glCreateVertexArrays(1, &floorVAO);
    glBindVertexArray(floorVAO);

    GLuint floorVBO;
    glGenBuffers(1, &floorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVerticies), &floorVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    GLuint coolPyramidVAO;
    glCreateVertexArrays(1, &coolPyramidVAO);
    glBindVertexArray(coolPyramidVAO);

    GLuint coolPyramidVBO;
    glGenBuffers(1, &coolPyramidVBO);
    glBindBuffer(GL_ARRAY_BUFFER, coolPyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coolPyramidVertices), &coolPyramidVertices, GL_STATIC_DRAW);


    GLuint coolPyramidIndices[] = {
        0, 1, 2,  // front
        2, 3, 4,  // back
        0, 3, 2,  // left
        2, 1, 4,  // right
        0, 1, 3,  // bottom
        3, 4, 1   // bottom
    };

    GLuint coolPyramidEBO;
    glGenBuffers(1, &coolPyramidEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coolPyramidEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coolPyramidIndices), coolPyramidIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // ==================== textures setup ==========================

    Texture scottTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "textures" / "scott.jpg", 0, GL_RGB };

    scottTexture.setWrapMethod(GL_REPEAT, GL_REPEAT);
    scottTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    scottTexture.createTexture();

    Texture wallTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "textures" / "wall.jpg", 0, GL_RGB };

    wallTexture.setWrapMethod(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    wallTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    wallTexture.createTexture();


    Texture floorTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "textures" / "mud.png", 0, GL_RGBA };

    floorTexture.setWrapMethod(GL_REPEAT, GL_REPEAT);
    floorTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    floorTexture.createTexture();



    // ======== texture units setup ========

    cubeShader.useShader();
    glUniform1i(glGetUniformLocation(cubeShader.getProgram(), "inTexture0"), 0);
    glUniform1i(glGetUniformLocation(cubeShader.getProgram(), "inTexture1"), 1);


    floorShader.useShader();
    glUniform1i(glGetUniformLocation(floorShader.getProgram(), "inTexture0"), 0);



    // ======== config stuff ========

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
    std::random_device rd{};
    std::mt19937 mt { rd() };
    std::uniform_real_distribution u_rel_num { 0.f, 1.f };
    float randomAngle { u_rel_num(mt) * 80 };

    float lastFrame {};
    float deltaTime {};

    // float floorYPos {-2.0f};
    int floorWidth  {3};
    int floorDepth  {3};
    float cellWidth {1.0f};
    float cellDepth {1.0f};

    // ======== camera setup ========
    Camera camera { window,  800, 600, 0.f, -90.f, 0.05f, 5.5f, glm::vec3{ 0.0f, 2.f, 4.5f }, glm::vec3{ 0.0f, 0.0f, -1.0f } };


    while (!glfwWindowShouldClose(window))
    {
        proccessInput(window);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            ++floorDepth;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && floorDepth > 0)
        {
            --floorDepth;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            ++floorWidth;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && floorWidth > 0)
        {
            --floorWidth;
        }

        glfwPollEvents();

        float time { static_cast<float>(glfwGetTime()) };
        deltaTime = time - lastFrame;
        lastFrame = time;

        camera.updatePosition(deltaTime);
        camera.cameraLog();
        


        // ========= background color ========

        float redVal    { cos(time * 0.5f) / 2.f + 0.6f};
        float greenVal  { sin(time * 0.7f) / 2.0f + 0.6f };
        float blueVal   { sin(time) / 2.f + 0.6f };

        glClearColor(redVal, greenVal, blueVal, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // ======== cubes drawing ========

        cubeShader.useShader();

        glActiveTexture(GL_TEXTURE0);
        scottTexture.bindTexture();

        glActiveTexture(GL_TEXTURE1);
        wallTexture.bindTexture();

        glBindVertexArray(cubeVAO);
        for (int i {0}; i < sizeof(cubePositions) / (cubePositions->length() * sizeof(float)); ++i)
        {
            glm::mat4 trans { 1.0f };
            glm::mat4 view { glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getDirection(), { 0.0f, 1.0f, 0.0f }) };
            glm::mat4 projection { glm::perspective(glm::radians(45.f), 800.f / 600, 0.1f, 100.f) };
            trans = glm::translate(trans, { cubePositions[i].x, cubePositions[i].y + 3.f, cubePositions[i].z - 4.f });
            trans = glm::rotate(trans, time * glm::radians(randomAngle * i + 10.f),  glm::vec3(1.0f, 0.3f, 0.5f));     

            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgram(), "modelMtx"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgram(), "viewMtx"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(cubeShader.getProgram(), "projectionMtx"), 1, GL_FALSE, glm::value_ptr(projection));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        // ======== pyramid drawing ========

        coolPyramidShader.useShader();
        glBindVertexArray(coolPyramidVAO);
        glm::mat4 model { 1.f };
        model = glm::translate(model, { 0.f, 0.f, 0.f});
        glm::mat4 view { glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getDirection(), glm::vec3(0.f, 1.f, 0.f))};
        glm::mat4 projection { glm::perspective(glm::radians(45.f), 800.f / 600, 0.1f, 100.f) };

        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "modelMtx"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "viewMtx"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "projectionMtx"), 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);



        // ========== floor drawing ==========

        floorShader.useShader();
        glActiveTexture(GL_TEXTURE0);
        floorTexture.bindTexture();


        glBindVertexArray(floorVAO);

        int xOffset { floorWidth / 2 };
        int zOffset { floorDepth / 2 };

        for (int i {0}; i < floorDepth; ++i)
        {
            for (int j {0}; j < floorWidth; ++j)
            {
                glm::mat4 model { 1.0f };
                model = glm::translate(model, glm::vec3(j * cellWidth - xOffset , 0.0f, i * cellDepth - zOffset));
                model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, 0.0f ));
                glm::mat4 view { glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getDirection(), { 0.0f, 1.0f, 0.0f }) };
                glm::mat4 projection { glm::perspective(glm::radians(45.f), 4 / (float)3, 0.1f, 100.f) };

                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

        }

        fmt::print(fg(fmt::color::yellow), "Floor width: {}, depth: {}\n\n", floorWidth, floorDepth);

        glfwSwapBuffers(window);  
    }


    // cleanup
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &floorVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &floorVAO);
    glfwTerminate();

    return 0;
}