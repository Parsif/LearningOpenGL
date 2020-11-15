#version 430 core

out vec4 fr_color;

in vec2 TexCoords;
struct Material
{
    sampler2D diffuse0;
};

uniform Material u_material;

void main()
{
    fr_color = texture(u_material.diffuse0, TexCoords);
}