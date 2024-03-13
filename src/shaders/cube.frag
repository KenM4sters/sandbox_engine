#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coord;

uniform Material material;
uniform Light cube_light;
uniform vec3 camera_pos;

void main() {
    // Ambient light
    vec3 ambient_shading = cube_light.ambient * texture(material.diffuse, tex_coord).rgb;
    // Diffuse cube_light
    vec3 normal_dir = normalize(normal);
    vec3 cube_light_dir = normalize(cube_light.position - frag_pos);
    float diffuse_angle = max(dot(normal_dir, cube_light_dir), 0.0);
    vec3 diffuse_shading = cube_light.diffuse * diffuse_angle * texture(material.diffuse, tex_coord).rgb;
    // Specular cube_light
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-cube_light_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), material.shininess);
    vec3 specular_shading = cube_light.specular * specular_intensity * material.specular;

    vec3 result = ambient_shading + diffuse_shading + specular_shading;
    FragColor = texture(material.diffuse, tex_coord); 
}