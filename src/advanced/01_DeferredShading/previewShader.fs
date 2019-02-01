#version 330 core
in vec2 UV;

out vec4 FragColor;

uniform sampler2D screenTexture;
uniform bool defaultMode;

void main()
{
    // Default
    if(defaultMode)
    {
        FragColor = vec4(texture(screenTexture, UV).rgb,1.0);
    }
    else { // Spec
        FragColor =  vec4(texture(screenTexture, UV).aaa,1.0);
    }
}