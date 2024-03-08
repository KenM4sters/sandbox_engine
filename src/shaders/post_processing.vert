#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex_cord;

out vec2 tex_cord;
void main() {
    glPosition = vec4(aPos, 0.0, 1.0);
    tex_cord = aTex_cord;
}