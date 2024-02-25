#version 330 core

in vec4 vertexColor;

out vec4 outVertexColor;

void main()
{
    outVertexColor = vertexColor;
}