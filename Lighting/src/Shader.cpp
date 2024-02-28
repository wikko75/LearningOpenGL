#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <fmt/color.h>
#include "utils.hpp"


Shader::Shader(const std::filesystem::path &vertexShaderPath, const std::filesystem::path &fragmentShaderPath)
{

    std::ifstream vertexShaderFile(vertexShaderPath, std::ios::in | std::ios::binary);
    std::ifstream fragmentShaderFile(fragmentShaderPath, std::ios::in | std::ios::binary);

    if (!vertexShaderFile.is_open())
    {
        fmt::print(fg(fmt::color::red), "Error loading shader!\nShader path incorect!\nPath: {}", vertexShaderPath.string());
        return;
    }

    if (!fragmentShaderFile.is_open())
    {
        fmt::print(fg(fmt::color::red), "Error loading shader!\nShader path incorect!\nPath: {}", fragmentShaderPath.string());
        return;
    }


    std::stringstream vertexBuffer {};
    std::stringstream fragmentBuffer {};

    vertexBuffer << vertexShaderFile.rdbuf();
    fragmentBuffer << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    std::string v_str { vertexBuffer.str() };
    std::string f_str { fragmentBuffer.str() };

    const char* vertexShaderData { v_str.c_str() };
    const char* fragmentShaderData { f_str.c_str() };


    GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderData, 0);
    glCompileShader(vertexShader);

    shaderStatusLogger(vertexShader);

    GLuint fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragmentShader, 1, &fragmentShaderData, 0);
    glCompileShader(fragmentShader);

    shaderStatusLogger(fragmentShader);


    // ---------- linking shaders -----------

    this->program = glCreateProgram();

    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);

    programStatusLogger(this->program);

    glDeleteShader(vertexShader);  
    glDeleteShader(fragmentShader);
}

void Shader::useShader() const noexcept
{
    glUseProgram(this->program);
}

GLuint Shader::getProgram() const noexcept
{
    return this->program;
}

void Shader::setUniform3f(const char* name, float v0, float v1, float v2) const
{
    glUniform3f(glGetUniformLocation(this->program, name), v0, v1, v2);
}

void Shader::setUniform4f(const char* name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(glGetUniformLocation(this->program, name), v0, v1, v2, v3);
}

void Shader::setUniformMatrix3f(const char* name, GLboolean transpose, const GLfloat *value) const
{
    glUniformMatrix3fv(glGetUniformLocation(this->program, name), 1, transpose, value);
}

void Shader::setUniformMatrix4f(const char* name, GLboolean transpose, const GLfloat *value) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, transpose, value);
}

