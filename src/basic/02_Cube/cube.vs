#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec4 N;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    N = model * vec4(aNormal,0.0);
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}