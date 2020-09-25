#version 330 core

out vec4 color;

in vec3 myColor;

void main()
{
    color = vec4(myColor, 1.f);
}