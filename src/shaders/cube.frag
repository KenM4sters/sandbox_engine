#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
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

uniform Material material;
uniform Light light;
uniform vec3 camera_pos;

void main() {
    // Ambient light
    vec3 ambient_shading = light.ambient * material.ambient;
    // Diffuse light
    vec3 normal_dir = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diffuse_angle = max(dot(normal_dir, light_dir), 0.0);
    vec3 diffuse_shading = light.diffuse * (diffuse_angle * material.diffuse);
    // Specular light
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-light_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), material.shininess);
    vec3 specular_shading = light.specular * specular_intensity * material.specular;

    vec3 result = ambient_shading + diffuse_shading + specular_shading;
    FragColor = vec4(result, 1.0); 
}