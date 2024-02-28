#version 330 core

out vec4 outEmittedColor;

uniform vec3 lightColor;

void main()
{
    outEmittedColor = vec4(lightColor, 1.0);
}