#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex_coord;
layout (location = 3) in vec3 aInstance_pos;

// uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 look_at_camera;
uniform vec3 camera_pos;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coord;

void main() {
    mat4 transform = view * model;

    vec3 CameraRight_worldspace = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 CameraUp_worldspace = vec3(view[0][1], view[1][1], view[2][1]);
    vec3 world_pos = vec3(
        aInstance_pos 
        + CameraRight_worldspace * aPos.x  
        + CameraUp_worldspace * aPos.y 
    );

	gl_Position = projection * transform * vec4(world_pos, 1.0);
	frag_pos = vec3(model * vec4(aPos + aInstance_pos, 1.0));
	tex_coord = aTex_coord;
    normal = mat3(transpose(inverse(model))) * aNormal; 
}