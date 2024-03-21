#version 330 core
out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

void main()
{  
    // Ambient light
    vec3 ambient_shading = light_cube.ambient * texture(texture_diffuse1, tex_coord).rgb;
    // Diffuse light_cube
    vec3 normal_dir = normalize(normal);
    vec3 light_cube_dir = normalize(light_cube.position - frag_pos);
    float diffuse_angle = max(dot(normal_dir, light_cube_dir), 0.0);
    vec3 diffuse_shading = light_cube.diffuse * diffuse_angle * texture(texture_diffuse1, tex_coord).rgb;
    // Specular light_cube
    vec3 view_dir = normalize(camera_pos - frag_pos);
    vec3 critical_reflection = reflect(-light_cube_dir, normal_dir);
    float specular_intensity = pow(max(dot(view_dir, critical_reflection), 0.0), 32.0);
    vec3 specular_shading = light_cube.specular * specular_intensity * texture(texture_specular1, tex_coord).rgb;

    vec3 result = ambient_shading + diffuse_shading + specular_shading;
    FragColor = vec4(result, 1.0); 

    // // FragColor = texture(texture_diffuse1, tex_coord);
    // FragColor = vec4(normal, 1.0);
}