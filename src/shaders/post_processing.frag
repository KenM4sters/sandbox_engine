#version 330 core

out vec4 FragColor;
in vec2 tex_cord;
uniform sampler2D tex;

void main() {
    FragColor = texture(tex, tex_cord);
    // vec4(vec3(1 - texture(tex, tex_cord)), 1.0)
}