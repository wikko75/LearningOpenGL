#version 330 core

in vec2 texCoor;

out vec4 FragColor;

uniform sampler2D inTexture0;

void main()
{
    FragColor = texture(inTexture0, texCoor);
}
