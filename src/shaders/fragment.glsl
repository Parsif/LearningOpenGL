#version 330 core

out vec4 color;

in vec2 fr_texturePos;

uniform vec3 u_light_color;
uniform vec3 u_object_color;

void main()
{
    color = vec4(u_light_color * u_object_color, 1.0f);
}