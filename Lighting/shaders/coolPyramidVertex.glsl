#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inVertexColor;
layout (location = 2) in vec3 inNormal;

out vec4 vertexColor;
out vec3 fragPos;
out vec3 normal;
out vec3 lightSrcPos;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;


uniform vec3 lightPos;
uniform mat3 normalMtx;

void main()
{
    gl_Position = projectionMtx * viewMtx * modelMtx * vec4(inPos, 1.0);
    vertexColor = inVertexColor;
    normal = normalMtx * inNormal;
    
    // light calculation in view space instead of world space
    fragPos = vec3(viewMtx * modelMtx * vec4(inPos, 1.0));
    lightSrcPos = vec3(viewMtx * vec4(lightPos, 1.0));
}