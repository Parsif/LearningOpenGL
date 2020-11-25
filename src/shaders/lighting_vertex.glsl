#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coords;

uniform mat4 u_model;
uniform mat4 u_view_projection;

out vec3 vs_normal;
out vec3 vs_frag_pos;
out vec2 vs_tex_coords;


void main()
{
    gl_Position = u_view_projection * u_model * vec4(position, 1.0f);
    vs_normal = mat3(transpose(inverse(u_model))) * normal;
    vs_frag_pos = vec3(u_model * vec4(position, 1.0f));
    vs_tex_coords = tex_coords;
}
