#version 430 core

struct DirLight {
    vec3 direction;

    vec3 albedo;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 albedo;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;

    float constant;
    float linear;
    float quadratic;

    vec3 albedo;
};

struct Material
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};

uniform DirLight u_dir_light;
uniform PointLight u_point_light;
uniform SpotLight u_spot_light;
uniform Material u_material;

uniform vec3 u_view_pos;

in vec3 vs_normal;
in vec3 vs_frag_pos;
in vec2 vs_tex_coords;

out vec4 fr_color;

vec3 calcDirLight(vec3 normal);
vec3 calcPointLight(vec3 normal);
vec3 caclSpotLight(vec3 normal);

void main()
{
    vec3 normal = normalize(vs_normal);
    vec4 color = vec4(calcPointLight(normal), 1.0f);
    fr_color = color;
}

vec3 calcDirLight(vec3 normal)
{
    vec3 ambient = u_dir_light.albedo * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Diffuse
    vec3 light_direction = normalize(-u_dir_light.direction);
    float diff_angle = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse = u_dir_light.albedo * diff_angle * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Specular
    vec3 view_direction = normalize(u_view_pos - vs_frag_pos);
    vec3 reflect_light_direction = reflect(-light_direction, normal);
    float specular_angle = pow(max(dot(view_direction, reflect_light_direction), 0.0f), u_material.shininess);
    vec3 specular = u_dir_light.albedo * specular_angle * vec3(texture(u_material.specular0, vs_tex_coords));

    return ambient + diffuse + specular;
}

vec3 calcPointLight(vec3 normal)
{
    vec3 ambient = u_point_light.albedo * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Diffuse
    vec3 light_direction = normalize(u_point_light.position - vs_frag_pos);
    float diff_angle = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse = u_point_light.albedo * diff_angle * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Specular
    vec3 view_direction = normalize(u_view_pos - vs_frag_pos);
    vec3 reflect_light_direction = reflect(-light_direction, normal);
    float specular_angle = pow(max(dot(view_direction, reflect_light_direction), 0.0f), u_material.shininess);
    vec3 specular = u_point_light.albedo * specular_angle * vec3(texture(u_material.specular0, vs_tex_coords));

    float distance = length(u_point_light.position - vs_frag_pos);
    float attenuation = 1.0f / (u_point_light.constant + u_point_light.linear * distance + u_point_light.quadratic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 caclSpotLight(vec3 normal)
{
    // Ambient
    vec3 ambient = u_spot_light.albedo * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Diffuse
    vec3 frag_to_src_light_direction = normalize(u_spot_light.position - vs_frag_pos);
    float diff_angle = max(dot(normal, frag_to_src_light_direction), 0.0f);
    vec3 diffuse = u_spot_light.albedo * diff_angle * vec3(texture(u_material.diffuse0, vs_tex_coords));

    // Specular
    vec3 view_direction = normalize(u_view_pos - vs_frag_pos);
    vec3 reflect_light_direction = reflect(-frag_to_src_light_direction, normal);
    float specular_angle = pow(max(dot(view_direction, reflect_light_direction), 0.0f), u_material.shininess);
    vec3 specular = u_spot_light.albedo * specular_angle * vec3(texture(u_material.specular0, vs_tex_coords));

    float distance = length(u_spot_light.position - vs_frag_pos);
    float attenuation = 1.0f / (u_spot_light.constant + u_spot_light.linear * distance + u_spot_light.quadratic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // spotlight (soft edges)
    float theta = dot(normalize(-u_spot_light.direction), frag_to_src_light_direction);
    float intensity = smoothstep(0.0f, 1.0f, (theta - u_spot_light.outer_cut_off) / (u_spot_light.cut_off - u_spot_light.outer_cut_off));
    diffuse *= intensity;
    specular *= intensity;

    return ambient + diffuse + specular;
}
