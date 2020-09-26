#version 330 core

out vec4 color;

in vec3 myColor;
in vec2 fr_texturePos;

uniform sampler2D our_texture;

void main()
{
    color = texture(our_texture, fr_texturePos);
}