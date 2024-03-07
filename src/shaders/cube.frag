#version 330 core

out vec4 FragColor;
in vec3 frag_pos;
in vec3 normal;

uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 camera_pos;

void main() {

    // Ambient light
    float ambient_strength = 0.4;   
    vec3 ambient = ambient_strength * light_color;
    // Diffuse light
    vec3 normal_dir = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diffuse_angle = max(dot(normal_dir, light_dir), 0.0);
    vec3 diffuse_shading = diffuse_angle * light_color;
    // Specular light
    float specular_strength = 0.8;
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-light_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), 32.0);
    vec3 specular_shading = specular_intensity * specular_strength * light_color;

    vec3 result = (ambient + diffuse_shading + specular_shading) * uColor;
    FragColor = vec4(result, 1.0);
}