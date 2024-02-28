#version 330 core

in vec3 normal;
in vec3 fragPos;

out vec4 outColor;

uniform vec3 lightSrcPos;
uniform vec3 lightSrcColor;
uniform vec3 objColor;
uniform vec3 cameraPos;


void main()
{
    float ambientStrenth = 0.1;
    float specularStrength = 0.5;

    vec3 ambient = vec3(ambientStrenth * lightSrcColor);

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightSrcPos - fragPos);
    vec3 diffusion = max(dot(norm, lightDir), 0.0) * lightSrcColor;

    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 refDir = reflect(-lightDir, norm);

    vec3 specular = pow(max(dot(cameraDir, refDir), 0.0), 8) * specularStrength * lightSrcColor;

    outColor =  vec4((ambient + diffusion + specular) * objColor, 1.0);
}