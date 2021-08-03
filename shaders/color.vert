#version 330
precision mediump float;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texcoord;

uniform mat4 u_model;
uniform mat3 u_normals_model;
uniform mat4 u_mvp;

void main()
{
	v_position = vec3(u_model * vec4(a_position, 1.));
	v_normal = normalize(u_normals_model * a_normal);
	v_texcoord = a_texcoord;

	gl_Position = u_mvp * vec4(a_position, 1.);
}
