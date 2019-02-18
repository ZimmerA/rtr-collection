#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;
out vec3 lightDir;

uniform mat4 model;
uniform mat4 mvp;
uniform vec3 lightPos;

void main()
{
    UV = aUV;
    lightDir = vec3(model * vec4(aPos.x, aPos.y, aPos.z, 1.0)) - lightPos;
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}