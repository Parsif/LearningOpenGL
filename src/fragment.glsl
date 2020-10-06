#version 330 core

out vec4 color;

in vec3 myColor;
in vec2 fr_texturePos;

uniform sampler2D u_face_texture;
uniform sampler2D u_container_texture;


void main()
{
    color = mix(texture(u_face_texture, fr_texturePos), texture(u_container_texture, fr_texturePos), 0.3);
}