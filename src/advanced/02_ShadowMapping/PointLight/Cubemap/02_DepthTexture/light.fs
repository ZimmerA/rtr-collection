#version 330 core
in vec2 UV;
in vec3 lightDir;

out vec4 FragColor;

uniform samplerCubeShadow shadowMap;
uniform sampler2D albedo;

uniform float near;
uniform float far;

float VectorToDepth (vec3 Vec)
{
    vec3 AbsVec = abs(Vec);
    float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));

    float NormZComp = (far+near) / (far-near) - (2*far*near)/(far-near)/LocalZcomp;
    return (NormZComp + 1.0) * 0.5;
}

void main()
{
    float currentDist = VectorToDepth(lightDir);

    float fShadow = 1.0 - texture(shadowMap, vec4(lightDir.xyz, currentDist));

    FragColor = vec4(texture(albedo, UV).rgb,1.0) * fShadow;
}