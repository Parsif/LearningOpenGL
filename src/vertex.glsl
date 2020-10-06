#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture_pos;


out vec3 myColor;
out vec2 fr_texturePos;

void main()
{
    gl_Position = vec4(position, 1.0);
    myColor = color;
    fr_texturePos = texture_pos;
}