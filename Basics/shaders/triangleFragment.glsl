#version 330 core
in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform vec4 color;  // changing colors
uniform sampler2D inTexture0;
uniform sampler2D inTexture1;

void main()
{
    FragColor = mix(texture(inTexture0, texCoord), texture(inTexture1, texCoord), 0.0);  // * vertexColor;
}