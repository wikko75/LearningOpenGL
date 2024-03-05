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

    void setUniformf(const char* name, float v0) const;

    void setUniform3f(const char* name, float v0, float v1, float v2) const;

    void setUniform4f(const char* name, float v0, float v1, float v2, float v3) const;

    void setUniformMatrix4f(const char* name, GLboolean transpose, const GLfloat *value) const;

    void setUniformMatrix3f(const char* name, GLboolean transpose, const GLfloat *value) const;

    ~Shader() = default;

private:
    GLuint program;
};

#endif