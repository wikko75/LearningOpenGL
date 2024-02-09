#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <filesystem>
#include <string>

class Shader
{
public:
    Shader(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader);
    void useShader() const noexcept;
    GLuint getProgram() const noexcept;
    ~Shader() = default;

    // TODO uniform var setters

private:
    GLuint program;
};

#endif