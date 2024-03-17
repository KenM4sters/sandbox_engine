#version 330 core

struct Material {
    sampler2D diffuse_forest;
    sampler2D  diffuse_salt;
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
in float tex_val;

uniform Material material;
uniform Light light_cube;
uniform vec3 camera_pos;

void main() {
    vec3 salt = texture(material.diffuse_salt, tex_coord).rgb;
    vec3 forest = texture(material.diffuse_forest, tex_coord).rgb;
    vec3 resultant_tex;
    if(frag_pos.y < 20.0)
        resultant_tex = forest.rgb;
    else
        resultant_tex = mix(forest, salt, min(1.0, (frag_pos.y - 20) / 5.0)).rgb;
    // Ambient light
    vec3 ambient_shading = light_cube.ambient * resultant_tex;
    // Diffuse light_cube
    vec3 normal_dir = normalize(normal);
    vec3 light_cube_dir = normalize(light_cube.position - frag_pos);
    float diffuse_angle = max(dot(normal_dir, light_cube_dir), 0.0);
    vec3 diffuse_shading = light_cube.diffuse * diffuse_angle * resultant_tex;
    // Specular light_cube
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-light_cube_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), material.shininess);
    vec3 specular_shading = light_cube.specular * specular_intensity * material.specular;

    vec3 result = ambient_shading + diffuse_shading + specular_shading;
    FragColor = vec4(result, 1.0); 
}