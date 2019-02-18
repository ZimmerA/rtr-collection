#version 330 core
in vec2 UV;
in vec3 lightDir;

out vec4 FragColor;

uniform samplerCube shadowMap;
uniform sampler2D albedo;

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1),
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);

void main()
{
    float currentDist = length(lightDir);
   // float sampledDist = texture(shadowMap, lightDir).r;

    // Apply slope scale bias
    //float ddistdx = dFdx(sampledDist);
    //float ddistdy = dFdy(sampledDist);
    //sampledDist += slopeBias * abs(ddistdx);
    //sampledDist += slopeBias * abs(ddistdy);

  //  float fShadow = (currentDist  - sampledDist - 0.15 < 0.0) ? 1.0 : 0.0;
    float shadow = 0.0;
    float bias   = 0.35;
    int samples  = 20;
    float diskRadius = 0.05;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(shadowMap, lightDir + sampleOffsetDirections[i] * diskRadius).r;
        if(currentDist - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    FragColor = vec4(texture(albedo, UV).rgb,1.0) * (1-shadow);
}