#version 430 core

out vec4 FragColor;

in vec2 TexCoords;
struct Material
{
    sampler2D diffuse0;
};

uniform Material u_material;

void main()
{
    FragColor = texture(u_material.diffuse0, TexCoords);
}