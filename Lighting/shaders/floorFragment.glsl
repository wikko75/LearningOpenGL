#version 330 core

in vec3 normal;
in vec2 texCoor;
in vec3 lightPos;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightColor;
uniform sampler2D inTexture0;

void main()
{
    float ambientStrength = 0.3;
    float specularStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor; 

    vec3 normalV = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = max(dot(normalV, lightDir), 0.0) * lightColor;

    vec3 lightRef = reflect(-lightDir, normalV);
    vec3 specular = pow(max(dot(lightRef, normalize(-fragPos)), 0.0), 8) * specularStrength * lightColor;   

    FragColor = vec4((ambient + diffuse + specular), 1.0) * texture(inTexture0, texCoor);
}
