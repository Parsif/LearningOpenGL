#version 330 core

uniform vec3 u_light_color;
uniform vec3 u_object_color;
uniform vec3 u_light_pos;
uniform vec3 u_view_pos;

in vec3 vs_normal;
in vec3 vs_frag_pos;

out vec4 color;

void main()
{
    // Ambient
    float amient_strength = 0.1f;
    vec3 ambient = amient_strength * u_light_color;

    // Diffuse
    vec3 normal = normalize(vs_normal);
    vec3 light_direction = normalize(u_light_pos - vs_frag_pos);
    float diff_angle = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse = diff_angle * u_light_color;

    // Specular
    vec3 view_direction = normalize(u_view_pos - vs_frag_pos);
    vec3 reflect_light_direction = reflect(-light_direction, normal);
    float specular_angle = pow(max(dot(view_direction, reflect_light_direction), 0.0f), 32);
    float specular_strength = 0.5f;
    vec3 specular = specular_angle * u_light_color * specular_strength;

    color = vec4((ambient + diffuse + specular) * u_object_color, 1.0f);
}