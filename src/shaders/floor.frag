#version 330 core

out vec4 FragColor;

uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * uColor;
    FragColor = vec4(uColor, 1.0);
}