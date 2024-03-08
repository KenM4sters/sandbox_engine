#version 330 core

in vec2 tex_cord;
uniform sampler2D texture;

void main() {
    Fragcolor = texture(texture, tex_cord);
}