#version 330 core
out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 frag_pos;
in vec2 tex_coord;
in vec3 normal;

uniform Light light_cube;
uniform vec3 camera_pos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform Material material;
uniform int nTextures;

void main()
{

    vec3 high_color = vec3(0, 0.506, 1);
    vec3 low_color = vec3(0, 0.67, 1);
    vec3 color = mix(low_color, high_color, min(frag_pos.y / 100.0, 1.0));
    FragColor = vec4(color, 1.0); 
}