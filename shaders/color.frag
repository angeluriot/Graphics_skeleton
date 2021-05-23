#version 140
precision mediump float;

varying vec3 v_positions;
varying vec3 v_normals;
varying vec2 v_uvs;

uniform vec3 u_camera;

uniform vec4 u_color;
uniform float u_ambient;
uniform float u_diffuse;
uniform float u_specular;
uniform float u_shininess;

uniform int[10] u_light_types;
uniform vec3[10] u_light_vectors;
uniform vec4[10] u_light_colors;
uniform float[10] u_light_intensities;
uniform int u_nb_lights;

uniform sampler2D u_texture;
uniform int u_textured;

void main()
{
	vec3 ambient_color = vec3(0., 0., 0.);
	vec3 diffuse_color = vec3(0., 0., 0.);
	vec3 specular_color = vec3(0., 0., 0.);
	vec3 reflection = vec3(0., 0., 0.);
	vec3 camera_direction = vec3(0., 0., 0.);
	vec3 light_direction = vec3(0., 0., 0.);
	float intensity = 0 ;

	for (int i = 0; i < u_nb_lights; i++)
	{
		light_direction = u_light_vectors[i];
		intensity = u_light_intensities[i];

		if (u_light_types[i] == 2)
		{
			light_direction = normalize(v_positions - u_light_vectors[i]);
			intensity = u_light_intensities[i] / distance(v_positions, u_light_vectors[i]);
		}

		// Ambiant
		ambient_color += ((1 - u_textured) * u_color.rgb + u_textured * texture2D(u_texture, v_uvs).rgb) * u_ambient * intensity;

		if (u_light_types[i] != 0)
		{
			// Diffuse
			diffuse_color += ((1 - u_textured) * u_color.rgb + u_textured * texture2D(u_texture, v_uvs).rgb) * u_diffuse * max(0., dot(v_normals, -light_direction)) * u_light_colors[i].rgb * intensity;

			// Specular
			vec3 reflection = reflect(light_direction, v_normals);
			vec3 camera_direction = normalize(u_camera - v_positions);
			specular_color += u_specular * pow(max(0., dot(reflection, camera_direction)), u_shininess) * u_light_colors[i].rgb * intensity;
		}
	}

	gl_FragColor = vec4(ambient_color + diffuse_color + specular_color, ((1 - u_textured) * u_color.a + u_textured * texture2D(u_texture, v_uvs).a));
}
