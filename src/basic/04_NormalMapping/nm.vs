#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 UV;
out vec3 tangentFragPos;
out vec3 tangentLightPos;
out vec3 tangentViewPos;

uniform mat4 mvp;
uniform mat4 model;

const vec3 viewPos = vec3(0.0, 0.0, 0.0);
const vec3 lightPos = vec3(0.0, 0.0, 160.0);

void main()
{
    UV = aUV;

    // Assuming only uniform scaling operations
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,0.0)));

    mat3 TBN = transpose(mat3(T,B,N));

    tangentFragPos = TBN * vec3(model * vec4(aPos,1.0));
    tangentLightPos = TBN * lightPos;
    tangentViewPos = TBN * viewPos;

    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}