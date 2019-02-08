#version 330 core

in vec2 UV;
in vec3 tangentFragPos;
in vec3 tangentLightPos;
in vec3 tangentViewPos;

out vec4 FragColor;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;

const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float specularStrength = 1.0;
const float specExp = 32;

void main()
{
    vec3 N = texture(normalMap, UV).xyz;
    N = normalize(N * 2.0 - 1.0);

    vec3 L = normalize(tangentLightPos - tangentFragPos);
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);

    vec3 R = reflect(-L, N);

    // calculate diffuse light
    float nDotL= max(dot(N, L), 0.0);
    vec3 diffuse = nDotL * lightColor;

    // Calculate specular light
    float specTerm = pow(max(dot(viewDir, R), 0.0), specExp);
    vec3 specular = specularStrength * specTerm * lightColor;

    vec3 resultColor =  (diffuse + specular) * vec3(texture(albedoMap, UV));
    FragColor = vec4(resultColor, 1.0);

}