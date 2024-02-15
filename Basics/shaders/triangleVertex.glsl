#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 transformMtx;

void main()
{
    gl_Position = transformMtx * vec4(aPos.xyz, 1.0);
    vertexColor = color;
    texCoord = aTexCoord;
}