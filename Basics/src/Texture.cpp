#include "Texture.hpp"
#include "stb_image.hpp"
#include <fmt/color.h>


Texture::Texture(const GLenum type, const std::filesystem::path& path, GLint LOD,  GLenum format) 
    : type {type}, LOD {LOD}, format {format}, texData {} 
{
    glGenTextures(1, &(this->id));
    glBindTexture(type, this->id);

    std::string texFile { path.string() };
    
    stbi_set_flip_vertically_on_load(true);  
    texData = stbi_load(texFile.c_str(), &(this->width), &(this->height), &(this->noOfChannels), 0);

    if (!texData)
    {
        fmt::print(fg(fmt::color::red), "Failed to load texture!\n");
        stbi_image_free(texData);
        return;
    }
}


void Texture::createTexture()
{
    switch (this->type)
    {
    case GL_TEXTURE_1D:
    
        // TODO
        // glTexImage1D()
        break;

    case GL_TEXTURE_2D:

        glTexImage2D(this->type, this->LOD, GL_RGB, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(type);
        stbi_image_free(texData);
        break;

    case GL_TEXTURE_3D:
        // TODO
    default:
        break;
    }
}


void Texture::setWrapMethod(GLint WRAP_S, GLint WRAP_R)
{
    glBindTexture(this->type, this->id);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, WRAP_S);
    glTexParameteri(this->type, GL_TEXTURE_WRAP_R, WRAP_R);
}


void Texture::setFilterMethod(GLint MIN_FILTER, GLint MAG_FILTER)
{
    glBindTexture(this->type, this->id);
    glTextureParameteri(this->type, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
    glTextureParameteri(this->type, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
}


void Texture::bindTexture() const noexcept
{
    glBindTexture(this->type, this->id);
}