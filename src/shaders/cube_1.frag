#version 330 core

out vec4 FragColor;
in vec3 Normal;

uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    FragColor = vec4(uColor, 1.0);
}