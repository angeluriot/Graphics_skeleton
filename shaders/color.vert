#version 140
precision mediump float;

attribute vec3 positions;
attribute vec3 normals;
attribute vec2 uvs;

varying vec3 v_positions;
varying vec3 v_normals;
varying vec2 v_uvs;

uniform mat4 u_model;
uniform mat3 u_inverted_model;
uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(positions, 1.);

	v_positions = vec3(u_model * vec4(positions, 1.));
	v_normals = normalize(u_inverted_model * normals);
	v_uvs = uvs;
}
