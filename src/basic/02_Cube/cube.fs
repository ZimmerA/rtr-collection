#version 330 core
out vec4 FragColor;
in vec4 N;
void main()
{

    FragColor = vec4(N.xyz, 1.0f);
}