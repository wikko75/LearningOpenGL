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

    // enum UniformType
    // {
    //     INT,
    //     FLOAT,
    //     VEC3f,
    //     VEC4f,
    //     MTX1f,
    //     MTX2f,
    //     MTX3f,
    //     MTX4f
    // };

    // void setsetUniform(UniformType type, )

    ~Shader() = default;



private:
    GLuint program;
};

#endif