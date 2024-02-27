#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;

void main()
{
    gl_Position = projectionMtx * viewMtx * modelMtx * vec4(aPos.xyz, 1.0);
}