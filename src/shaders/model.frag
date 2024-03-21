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
    // Ambient light
    vec3 ambient_shading = light_cube.ambient;
    // Diffuse light_cube
    vec3 normal_dir = normalize(normal);
    vec3 light_cube_dir = normalize(light_cube.position - frag_pos);
    float diffuse_angle = max(dot(normal_dir, light_cube_dir), 0.0);
    vec3 diffuse_shading = light_cube.diffuse * diffuse_angle;
    // Specular light_cube
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-light_cube_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), 32.0);
    vec3 specular_shading = light_cube.specular * specular_intensity;

    if(nTextures > 0) {
        ambient_shading *= texture(texture_diffuse1, tex_coord).rgb;
        diffuse_shading *= texture(texture_diffuse1, tex_coord).rgb;
        specular_shading *= texture(texture_specular1, tex_coord).rgb;
    } else {
        ambient_shading *= material.ambient;
        diffuse_shading *= material.diffuse;
        specular_shading *= material.specular * material.shininess;
    }

    vec3 result = ambient_shading + diffuse_shading + specular_shading;
    FragColor = vec4(result, 1.0); 

    // FragColor = texture(texture_diffuse1, tex_coord);
    // FragColor = vec4(normal, 1.0);
}