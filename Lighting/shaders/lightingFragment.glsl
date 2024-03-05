#version 330 core

in vec3 normal;
in vec3 fragPos;

out vec4 outColor;


struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shinness;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 diffusion = max(dot(norm, lightDir), 0.0) * light.diffuse * material.diffuse;

    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 refDir = reflect(-lightDir, norm);

    float specularVal = pow(max(dot(cameraDir, refDir), 0.0), material.shinness);
    vec3 specular = light.specular * specularVal * material.specular;

    outColor =  vec4( ambient + diffusion + specular, 1.0 );
}