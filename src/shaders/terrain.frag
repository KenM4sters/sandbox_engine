#version 330 core

struct Material {
    sampler2D diffuse_middle;
    sampler2D diffuse_top;
    sampler2D diffuse_bottom;
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
    vec3 top = texture(material.diffuse_top, tex_coord).rgb;
    vec3 middle = texture(material.diffuse_middle, tex_coord).rgb;
    vec3 bottom = texture(material.diffuse_bottom, tex_coord).rgb;
    vec3 resultant_tex;
    if(frag_pos.y < 17.0 && frag_pos.y > 10.0) {
        resultant_tex = middle.rgb;
    } else if(frag_pos.y <= 10.0)
        resultant_tex = mix(middle, bottom, min(1.0, (10 - frag_pos.y) / 10.0)).rgb;
    else 
        resultant_tex = mix(middle, top, min(1.0, (frag_pos.y - 17) / 10.0)).rgb;
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