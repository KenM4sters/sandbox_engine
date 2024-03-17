#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex_coord;
layout (location = 5) in float aTexel_val;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coord;
out float tex_val;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	frag_pos = vec3(model * vec4(aPos, 1.0));
	tex_coord = aTex_coord;
	tex_val = aTexel_val;
	normal = mat3(transpose(inverse(model))) * aNormal;
}