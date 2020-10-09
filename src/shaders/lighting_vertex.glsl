#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 vs_normal;
out vec3 vs_frag_pos;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
    vs_normal = mat3(transpose(inverse(u_model))) * normal;
    vs_frag_pos = vec3(u_model * vec4(position, 1.0f));
}