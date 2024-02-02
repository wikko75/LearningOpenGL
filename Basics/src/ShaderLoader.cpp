#include "ShaderLoader.hpp"
#include <fstream>
#include <sstream>
#include <fmt/color.h>

std::string ShaderLoader::loadShader(const std::filesystem::path& path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        fmt::print(fg(fmt::color::red), "Error loading shader!\nShader path incorect!\n");
        return {};
    }

    std::stringstream buffer {};
    buffer << file.rdbuf();
    
    return buffer.str(); 
}