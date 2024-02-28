#version 330 core

in vec4 vertexColor;
in vec3 fragPos;
in vec3 normal;
in vec3 lightSrcPos;

out vec4 outVertexColor;

uniform vec3 lightSrcColor;

void main()
{
    float ambientStrength = .3;
    float specularStrength = 0.8;
    vec4 ambient = vec4(ambientStrength * lightSrcColor, 1.0);

    vec3 normalVec = normalize(normal);
    vec3 lightDir = normalize(lightSrcPos - fragPos);
    vec4 diffuse = vec4( max( dot(lightDir, normalVec), 0.0  ) * lightSrcColor, 1.0);

    vec3 lightRef = reflect(-lightDir, normalVec);
    vec4 specular = pow( max( dot(vec3(0.0), lightRef), 0.0 ), 200 ) * vec4(lightSrcColor, 1.0) * specularStrength;


    outVertexColor = (ambient + diffuse + specular) * vertexColor;
}