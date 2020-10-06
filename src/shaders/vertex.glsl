#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture_pos;

out vec2 fr_texturePos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
    fr_texturePos = texture_pos;
}