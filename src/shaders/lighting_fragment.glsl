#version 330 core

struct Material
{
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};

uniform Material u_material;
uniform Light u_light;

uniform vec3 u_object_color;
uniform vec3 u_view_pos;

in vec3 vs_normal;
in vec3 vs_frag_pos;

out vec4 color;

void main()
{
    // Ambient
    vec3 ambient = u_light.ambient * u_material.ambient;

    // Diffuse
    vec3 normal = normalize(vs_normal);
    vec3 light_direction = normalize(u_light.position - vs_frag_pos);
    float diff_angle = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse = u_light.diffuse * u_material.diffuse * diff_angle;

    // Specular
    vec3 view_direction = normalize(u_view_pos - vs_frag_pos);
    vec3 reflect_light_direction = reflect(-light_direction, normal);
    float specular_angle = pow(max(dot(view_direction, reflect_light_direction), 0.0f), u_material.shininess);
    vec3 specular = u_light.specular * u_material.specular * specular_angle;

    color = vec4((ambient + diffuse + specular) * u_object_color, 1.0f);
}