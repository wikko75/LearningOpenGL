#include <GL/glew.h>
#include <fmt/color.h>
#include "utils.hpp"
// delete core.h


void initLog() noexcept
{
    const char* version  { reinterpret_cast<const char*>(glGetString(GL_VERSION)) };
    const char* renderer { reinterpret_cast<const char*>(glGetString(GL_RENDERER)) };
    const char* vendor   { reinterpret_cast<const char*>(glGetString(GL_VENDOR)) };

    
    fmt::print(fg(fmt::color::yellow), "OpenGL version: {}\n", version);
    fmt::print(fg(fmt::color::yellow), "Renderer: {}\n",  renderer);
    fmt::print(fg(fmt::color::yellow), "Vendor: {}\n",  vendor);

    int profile;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);

    if (profile & GL_CONTEXT_CORE_PROFILE_BIT) 
    {
        fmt::print(fg(fmt::color::yellow), "OpenGL profile: Core\n");
    } 
    else if (profile & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) 
    {
        fmt::print(fg(fmt::color::yellow), "OpenGL profile: Compatibility\n");
    }

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    fmt::print(fg(fmt::color::yellow), "Maximum nr of vertex attributes supported: {}\n", nrAttributes);
}


void shaderStatusLogger(GLuint shader)
{
    char log[512];
    int STATUS_OK {0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &STATUS_OK);

    if (!STATUS_OK)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        fmt::print(fg(fmt::color::red), "Shader: {}\nShader compilation failed!\nLOG: {}", shader, log);
    }
}


void programStatusLogger(GLuint program)
{
    char log[512];
    int STATUS_OK {0};
    glGetProgramiv(program, GL_LINK_STATUS, &STATUS_OK);

    if (!STATUS_OK)
    {
        glGetProgramInfoLog(program, 512, NULL, log);
        fmt::print(fg(fmt::color::red), "Program: {}\nProgram linking failed!\nLOG: {}", program, log);
    }
}


void proccessInput(GLFWwindow *window) noexcept
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        fmt::print(fg(fmt::color::green), "Exiting...\n");
        glfwSetWindowShouldClose(window, true);
        return;
    }
}


void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
