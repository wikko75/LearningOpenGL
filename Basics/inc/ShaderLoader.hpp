#ifndef SHADER_LOADER_HPP
#define SHADER_LOADER_HPP

#include <filesystem>
#include <string>

class ShaderLoader
{
public:
    static std::string loadShader(const std::filesystem::path& path);  
};

#endif