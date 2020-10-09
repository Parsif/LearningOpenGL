#version 330 core

uniform vec3 u_light_color;
uniform vec3 u_object_color;
uniform vec4 u_light_pos;

in vec3 vs_normal;

out vec4 color;
in vec4 vs_frag_pos;

void main()
{
    float amient_strength = 0.1f;
    vec3 ambient = amient_strength * u_light_color;

    vec4 normal = normalize(vec4(vs_normal, 1.0f));
    vec4 light_direction = normalize(vs_frag_pos - u_light_pos);
    float diff_angle = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse = diff_angle * u_light_color;

    color = vec4((diffuse + ambient) * u_object_color, 1.0f);
}