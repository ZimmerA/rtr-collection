#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 viewPos;

void main()
{
    vec3 FragPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Albedo = texture(gAlbedoSpec, UV).rgb;
    float Specular = texture(gAlbedoSpec, UV).a;

    vec3 lighting = Albedo * 0.1;
    vec3 viewDir = normalize(viewPos - FragPos);

    // Single light at position (0,0,10)
    vec3 lightDir = normalize(vec3(0.0,0.0,10.0) - FragPos);

    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * vec3(1.0);
    lighting += diffuse;
    FragColor = vec4(lighting, 1.0);
}