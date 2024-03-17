#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex_coord;
layout (location = 3) in vec3 aInstance_pos;

// uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos + aInstance_pos, 1.0);
	frag_pos = vec3(model * vec4(aPos, 1.0));
	tex_coord = aTex_coord;
    normal = mat3(transpose(inverse(model))) * aNormal; 
}