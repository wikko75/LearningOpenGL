#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;

uniform mat3 normalMtx;

void main()
{
    gl_Position = projectionMtx * viewMtx *  modelMtx * vec4(inPos, 1.0);
    normal = normalMtx * inNormal;
    fragPos = vec3(modelMtx * vec4(inPos, 1.0));
}