#version 330 core
in vec2 UV;

out vec4 FragColor;

void main()
{
    FragColor = vec4(UV, 0.2f, 1.0f);
}