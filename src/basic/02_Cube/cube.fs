#version 330 core
in vec4 N;

out vec4 FragColor;

void main()
{
    FragColor = vec4(N.xyz, 1.0f);
}