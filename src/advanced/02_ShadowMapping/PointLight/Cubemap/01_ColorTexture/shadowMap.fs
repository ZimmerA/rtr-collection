#version 330 core
in vec2 UV;
in vec3 lightDir;

out float FragColor;

void main()
{
    float dist = length(lightDir);
    FragColor  = dist;
}