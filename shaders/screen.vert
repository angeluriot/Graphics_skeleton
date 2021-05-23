#version 140
precision mediump float;

attribute vec3 positions;
attribute vec2 uvs;

varying vec2 v_uvs;

void main()
{
	gl_Position = vec4(positions, 1.);
	v_uvs = uvs;
}
