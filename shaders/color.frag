#version 140
precision mediump float;

struct Material
{
	vec4 color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

struct Light
{
	int type;
	vec3 vector;
	vec4 color;
	float intensity;
};

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texcoord;

uniform vec3 u_camera;

uniform Material u_material;

const int nb_lights_max = 10;
uniform int[nb_lights_max] u_light_types;
uniform vec3[nb_lights_max] u_light_vectors;
uniform vec4[nb_lights_max] u_light_colors;
uniform float[nb_lights_max] u_light_intensities;
uniform int u_nb_lights;

uniform sampler2D u_texture;
uniform int u_textured;

void main()
{
	Light[nb_lights_max] lights;

	for (int i = 0; i < u_nb_lights; i++)
	{
		lights[i].type = u_light_types[i];
		lights[i].vector = u_light_vectors[i];
		lights[i].color = u_light_colors[i];
		lights[i].intensity = u_light_intensities[i];
	}

	vec3 ambient_color = vec3(0., 0., 0.);
	vec3 diffuse_color = vec3(0., 0., 0.);
	vec3 specular_color = vec3(0., 0., 0.);
	vec3 reflection = vec3(0., 0., 0.);
	vec3 camera_direction = vec3(0., 0., 0.);
	vec3 light_direction = vec3(0., 0., 0.);
	float intensity = 0 ;

	for (int i = 0; i < u_nb_lights; i++)
	{
		light_direction = lights[i].vector;
		intensity = lights[i].intensity;

		if (lights[i].type == 2)
		{
			light_direction = normalize(v_position - lights[i].vector);
			intensity = lights[i].intensity / distance(v_position, lights[i].vector);
		}

		// Ambiant
		ambient_color += ((1 - u_textured) * u_material.color.rgb + u_textured * texture2D(u_texture, v_texcoord).rgb) * u_material.ambient * intensity;

		if (lights[i].type != 0)
		{
			// Diffuse
			diffuse_color += ((1 - u_textured) * u_material.color.rgb + u_textured * texture2D(u_texture, v_texcoord).rgb) * u_material.diffuse * max(0., dot(v_normal, -light_direction)) * lights[i].color.rgb * intensity;

			// Specular
			vec3 reflection = reflect(light_direction, v_normal);
			vec3 camera_direction = normalize(u_camera - v_position);
			specular_color += u_material.specular * pow(max(0., dot(reflection, camera_direction)), u_material.shininess) * lights[i].color.rgb * intensity;
		}
	}

	gl_FragColor = vec4(ambient_color + diffuse_color + specular_color, ((1 - u_textured) * u_material.color.a + u_textured * texture2D(u_texture, v_texcoord).a));
}
