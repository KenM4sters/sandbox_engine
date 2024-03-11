#version 330 core
out vec4 FragColor;

in vec3 tex_coords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, tex_coords);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}