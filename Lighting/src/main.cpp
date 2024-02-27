#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.hpp"
#include "stb_image_resize2.h"
#include <string>
#include <filesystem>
#include "utils.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"


int main()
{

    if(glfwInit() != GLFW_TRUE)
    {
        fmt::print(fg(fmt::color::red), "Initializing GLFW failed!\n");
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window { glfwCreateWindow(800, 600, "Learning OpenGL!", NULL, NULL) };


    // ------- window icon setup ---------

    int width {};
    int height {};
    int channels_in_file {};
    std::string iconFile { (std::filesystem::current_path() / "res" / "textures" / "scott.jpg").string() };
    stbi_set_flip_vertically_on_load(true);
    int desiredWidth {40};
    int desiredHeight {40};
    unsigned char* iconData  { stbi_load(iconFile.c_str(), &width, &height, &channels_in_file, 0) };
    unsigned char* iconResized { stbir_resize_uint8_srgb(iconData, width, height, 0, iconData, desiredWidth, desiredHeight, 0, (stbir_pixel_layout)channels_in_file)};
    GLFWimage icon { desiredWidth, desiredHeight, iconResized };

    glfwSetWindowIcon(window, 1, &icon);
    stbi_image_free(iconData);
    
    
    glfwMakeContextCurrent(window);


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


    Shader lightingShader { std::filesystem::current_path() / "shaders" / "lightingVertex.glsl",
                            std::filesystem::current_path() / "shaders" / "lightingFragment.glsl"};


    Shader cubeLightShader { std::filesystem::current_path() / "shaders" / "lightingVertex.glsl",
                             std::filesystem::current_path() / "shaders" / "cubeLightFragment.glsl"};



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

    // TODO optimize - remove redundent data
    float cubeVertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,    // pos | normal | tex coor
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };
    
    // TODO optimize - remove redundent data
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



    // ================= VAO / VBO  setup ====================

    GLuint cubeVAO;
    glCreateVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    GLuint cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);


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

    GLubyte coolPyramidIndices[] = {
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


    GLuint lightVAO;
    glCreateVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);


    // ===========textures setup =============

    Texture floorTexture { GL_TEXTURE_2D, std::filesystem::current_path() / "res" / "textures" / "mud.png", 0, GL_RGBA };

    floorTexture.setWrapMethod(GL_REPEAT, GL_REPEAT);
    floorTexture.setFilterMethod(GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);
    floorTexture.createTexture();



    // ======== texture units setup ========

    floorShader.useShader();
    glUniform1i(glGetUniformLocation(floorShader.getProgram(), "inTexture0"), 0);



    // ======== config stuff ========

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    float lastFrame {};
    float deltaTime {};

    // float floorYPos {-2.0f};
    int floorWidth  {5};
    int floorDepth  {5};
    float cellWidth {1.0f};
    float cellDepth {1.0f};

    // ======== camera setup ========
    Camera camera { window,  800, 600, 0.f, -90.f, 0.05f, 5.5f, glm::vec3{ 0.0f, 1.5f, 4.5f }};


    glm::mat4 model { 1.f };
    glm::mat4 view {};
    glm::mat4 projection {};
    glm::mat3 normalMatrix {};

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

        view = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getDirection(), { 0.0f, 1.0f, 0.0f });
        projection = glm::perspective(glm::radians(45.f), 800.f / 600, 0.1f, 100.f);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // ======== pyramid drawing ========

        coolPyramidShader.useShader();
        glBindVertexArray(coolPyramidVAO);

        model = glm::mat4(1.0f);
        model = glm::translate(model, { -1.f, 0.f, 0.f});

        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "modelMtx"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "viewMtx"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(coolPyramidShader.getProgram(), "projectionMtx"), 1, GL_FALSE, glm::value_ptr(projection));

        // glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, 0);



        // ======== light source drawing ========

        cubeLightShader.useShader();
        glBindVertexArray(lightVAO);

        glm::vec3 lightPos { -3 *  sin(time), 1.f, 3 * cos(time) };

        fmt::println("Time elapsed: {}", time);

        model = glm::mat4(1.f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.3f));

        glUniformMatrix4fv(glGetUniformLocation(cubeLightShader.getProgram(), "modelMtx"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(cubeLightShader.getProgram(), "viewMtx"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(cubeLightShader.getProgram(), "projectionMtx"), 1, GL_FALSE, glm::value_ptr(projection));

        glDrawArrays(GL_TRIANGLES, 0, 36);



        // ======== cube drawing ========

        lightingShader.useShader();
        glBindVertexArray(cubeVAO);

        model = glm::mat4(1.0f);
        model = glm::translate(model, { 0.f, 0.5f, 0.f }); 
        model = glm::rotate(model, glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f)); 
        model = glm::rotate(model, 2 * time, glm::vec3(0.f, 1.f, 0.f)); 
        model = glm::scale(model, {.5f, 3.5f, .3f});

        normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

        glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgram(), "modelMtx"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgram(), "viewMtx"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgram(), "projectionMtx"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix3fv(glGetUniformLocation(lightingShader.getProgram(), "normalMtx"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glUniform3f(glGetUniformLocation(lightingShader.getProgram(), "lightSrcColor"), 1.f, 1.f, 1.f);
        glUniform3f(glGetUniformLocation(lightingShader.getProgram(), "objColor"), 1.f, 0.2f, 0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.getProgram(), "lightSrcPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.getProgram(), "cameraPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

        glDrawArrays(GL_TRIANGLES, 0, 36);


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
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(j * cellWidth - xOffset , 0.0f, i * cellDepth - zOffset));
                model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, 0.0f ));

                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(floorShader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

                // glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        fmt::print(fg(fmt::color::yellow), "Floor width: {}, depth: {}\n\n", floorWidth, floorDepth);

        glfwSwapBuffers(window);  
    }


    // cleanup
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &floorVBO);
    glDeleteBuffers(1, &coolPyramidVBO);
    glDeleteBuffers(1, &coolPyramidEBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteVertexArrays(1, &coolPyramidVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glfwTerminate();

    return 0;
}