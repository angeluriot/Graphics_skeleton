#version 140
precision mediump float;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texcoord;

uniform mat4 u_model;
uniform mat3 u_normals_model;
uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(a_position, 1.);

	v_position = vec3(u_model * vec4(a_position, 1.));
	v_normal = normalize(u_normals_model * a_normal);
	v_texcoord = a_texcoord;
}
