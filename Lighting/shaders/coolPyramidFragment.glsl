#version 330 core

in vec4 vertexColor;
in vec3 fragPos;
in vec3 normal;

out vec4 outVertexColor;

uniform vec3 lightSrcColor;
uniform vec3 lightSrcPos;

void main()
{
    float ambientStrenth = 0.5;
    vec4 ambient = max(ambientStrenth * vec4(lightSrcColor, 1.0), 0.0);
    outVertexColor = ambient * vertexColor;
}