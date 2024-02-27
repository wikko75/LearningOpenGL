#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <filesystem>


class Texture
{
public:
    Texture(const GLenum type, const std::filesystem::path& path, GLint LOD,  GLenum format);

    void createTexture();

    void bindTexture() const noexcept;

    void setWrapMethod(GLint WRAP_S, GLint WRAP_T);
    
    void setFilterMethod(GLint MIN_FILTER, GLint MAG_FILTER);

private:
    GLuint id;
    GLenum type;
    GLint LOD;
    GLenum format;
    int width;
    int height;
    int noOfChannels;
    unsigned char* texData;
};

#endif