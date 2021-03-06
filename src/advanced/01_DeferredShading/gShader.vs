#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    Normal = mat3(model) * aNormal;
    TexCoords = aUV;
    FragPos = mat3(model) * aPos;
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}