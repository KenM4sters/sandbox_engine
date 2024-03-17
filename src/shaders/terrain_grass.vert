#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex_coord;
layout (location = 3) in vec3 aInstance_pos;

// uniform vec3 uColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 camera_pos;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coord;

void main()
{
	// float dot_product = dot(aNormal, camera_pos);
	// float rot_angle = acos(dot_product / (length(aNormal) * length(camera_pos)));
	// float cosTheta = cos(rot_angle);
    // float sinTheta = sin(rot_angle);
    // float oneMinusCos = 1.0 - cosTheta;
	// // axis
    // vec3 normalizedAxis = normalize(vec3(0.0, 1.0, 0.0));
    // float x = normalizedAxis.x;
    // float y = normalizedAxis.y;
    // float z = normalizedAxis.z;
    // // Construct the rotation matrix
    // mat4 rotation_matrix = mat4(
    //     cosTheta + x * x * oneMinusCos,     x * y * oneMinusCos - z * sinTheta,  x * z * oneMinusCos + y * sinTheta,  0.0,
    //     y * x * oneMinusCos + z * sinTheta, cosTheta + y * y * oneMinusCos,      y * z * oneMinusCos - x * sinTheta,  0.0,
    //     z * x * oneMinusCos - y * sinTheta, z * y * oneMinusCos + x * sinTheta,  cosTheta + z * z * oneMinusCos,      0.0,
    //     0.0,                                0.0,                                 0.0,                                 1.0
    // );
	// mat4 new_model = model * rotation_matrix;

	gl_Position = projection * view * new_model * vec4(aPos + aInstance_pos, 1.0);
	frag_pos = vec3(model * vec4(aPos, 1.0));
	tex_coord = aTex_coord;
    normal = mat3(transpose(inverse(model))) * aNormal; 
}