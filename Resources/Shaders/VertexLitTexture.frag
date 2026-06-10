#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 Color;

// texture samplers
uniform sampler2D image;

void main()
{
    // texture
    vec4 objectColor = texture(image, TexCoord);
    FragColor = vec4(Color, 1.0) * objectColor;
}