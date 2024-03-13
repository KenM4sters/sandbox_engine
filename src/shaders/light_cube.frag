#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};


out vec4 FragColor;
in vec2 tex_coord;

uniform Material material;

void main() {
    FragColor = texture(material.diffuse, tex_coord);
}