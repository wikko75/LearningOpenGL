#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoor;

out vec3 normal;
out vec2 texCoor;
out vec3 lightPos;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalMtx;
uniform vec3 lightWorldPos;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    normal = normalMtx * inNormal;
    texCoor = inTexCoor;
    fragPos = vec3(view * model * vec4(inPos, 1.0));
    lightPos = vec3(view * vec4(lightWorldPos, 1.0));
}