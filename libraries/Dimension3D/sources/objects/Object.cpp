#include "dim/dimension3D.h"

namespace dim
{
	Object::Object(const Mesh& mesh, const Material& material)
	{
		this->mesh = mesh;
		this->material = material;
		vertex_buffer.set_shader("default");
		vertex_buffer.send_data(this->mesh);
		scaling_matrix = glm::mat4(1.f);
		rotation_matrix = glm::mat4(1.f);
		translation_matrix = glm::mat4(1.f);
		origin_matrix = glm::mat4(1.f);
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
		binded = false;
	}

	void Object::set_shader(const std::string shader_name)
	{
		vertex_buffer.set_shader(shader_name);
		vertex_buffer.send_data(mesh);
	}

	void Object::set_shader(Shader& shader)
	{
		vertex_buffer.set_shader(shader);
		vertex_buffer.send_data(mesh);
	}

	void Object::set_texture(const std::string texture_name)
	{
		vertex_buffer.textures.clear();
		vertex_buffer.add_texture(texture_name);
	}

	void Object::set_texture(Texture& texture)
	{
		vertex_buffer.textures.clear();
		vertex_buffer.add_texture(texture);
	}

	void Object::set_mesh(const Mesh& mesh)
	{
		this->mesh = mesh;
		vertex_buffer.send_data(mesh);
	}

	void Object::set_size(const Vector3& new_size)
	{
		scaling_matrix = glm::scale(glm::mat4(1.f), new_size.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_rotation(float new_rotation, const Vector3& new_axis)
	{
		rotation_matrix = glm::rotate(glm::mat4(1.f), new_rotation, new_axis.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_position(const Vector3& new_position)
	{
		translation_matrix = glm::translate(glm::mat4(1.f), new_position.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_origin(const Vector3& new_origin)
	{
		origin_matrix = glm::translate(glm::mat4(1.f), new_origin.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::scale(const Vector3& scale)
	{
		scaling_matrix = glm::scale(scaling_matrix, scale.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::rotate(float rotation, const Vector3& axis)
	{
		rotation_matrix = glm::rotate(rotation_matrix, rotation, axis.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::move(const Vector3& movement)
	{
		translation_matrix = glm::translate(translation_matrix, movement.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	Vector3 Object::get_size() const
	{
		return Vector4(scaling_matrix * glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	glm::mat4 Object::get_rotation() const
	{
		return rotation_matrix;
	}

	Vector3 Object::get_position() const
	{
		return Vector4(translation_matrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	Vector3 Object::get_origin() const
	{
		return Vector4(origin_matrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	void Object::bind()
	{
		vertex_buffer.shader->bind();

		for (auto& texture : vertex_buffer.textures)
			texture->bind();

		vertex_buffer.bind();
		binded = true;
	}

	void Object::unbind()
	{
		vertex_buffer.shader->unbind();

		for (auto& texture : vertex_buffer.textures)
			texture->unbind();

		vertex_buffer.unbind();
		binded = false;
	}

	void Object::draw(const Scene& scene, const Camera& camera, const std::vector<Light>& lights, DrawType draw_type) const
	{
		if (vertex_buffer.nb_vertices)
		{
			if (scene != Scene::window)
				scene.get_frame_buffer().bind();

			if (!binded)
			{
				vertex_buffer.shader->bind();

				for (auto& texture : vertex_buffer.textures)
					texture->bind();

				vertex_buffer.bind();
			}

			// Matrices

			vertex_buffer.send_uniform("u_model", model);
			vertex_buffer.send_uniform("u_inverted_model", glm::transpose(glm::inverse(glm::mat3(model))));
			vertex_buffer.send_uniform("u_mvp", camera.get_matrix() * model);

			// Camera

			vertex_buffer.send_uniform("u_camera", camera.get_position());

			// Materials

			vertex_buffer.send_uniform("u_color", material.get_color());
			vertex_buffer.send_uniform("u_ambient", material.get_ambient());
			vertex_buffer.send_uniform("u_diffuse", material.get_diffuse());
			vertex_buffer.send_uniform("u_specular", material.get_specular());
			vertex_buffer.send_uniform("u_shininess", material.get_shininess());

			// Lights

			std::vector<int> light_types;
			std::vector<Vector3> light_vectors;
			std::vector<sf::Color> light_colors;
			std::vector<float> light_intensities;

			for (auto& light : lights)
			{
				light_types.push_back(static_cast<int>(light.get_type()));
				light_vectors.push_back(light.get_vector());
				light_colors.push_back(light.get_color());
				light_intensities.push_back(light.get_intensity());
			}

			vertex_buffer.send_uniform("u_light_types", light_types);
			vertex_buffer.send_uniform("u_light_vectors", light_vectors);
			vertex_buffer.send_uniform("u_light_colors", light_colors);
			vertex_buffer.send_uniform("u_light_intensities", light_intensities);
			vertex_buffer.send_uniform("u_nb_lights", static_cast<int>(lights.size()));

			// Textures

			if (vertex_buffer.textures.size())
			{
				GLint u_texture = glGetUniformLocation(vertex_buffer.shader->get_id(), "u_texture");
				glUniform1i(u_texture, 0);

				vertex_buffer.send_uniform("u_textured", 1);
			}

			else
				vertex_buffer.send_uniform("u_textured", 0);

			glDrawArrays((GLenum)draw_type, 0, vertex_buffer.nb_vertices);

			if (!binded)
			{
				vertex_buffer.shader->unbind();

				for (auto& texture : vertex_buffer.textures)
					texture->unbind();

				vertex_buffer.unbind();
			}

			if (scene != Scene::window)
				scene.get_frame_buffer().unbind();
		}
	}
}
