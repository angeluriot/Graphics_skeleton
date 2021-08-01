#include "dim/dimension3D.hpp"

namespace dim
{
	void Object::draw(const Camera& camera, const std::vector<Light>& lights, DrawType draw_type, bool scene_shader) const
	{
		if (vertex_buffer.get_nb_vertices())
		{
			// Bind

			if (!binded)
			{
				shader.bind();
				texture.bind();
				vertex_buffer.bind();
			}

			// Matrices

			shader.send_uniform("u_model", model);
			shader.send_uniform("u_normals_model", glm::transpose(glm::inverse(glm::mat3(model))));
			shader.send_uniform("u_mvp", camera.get_matrix() * model);

			// Camera

			if (!scene_shader)
				shader.send_uniform("u_camera", camera.get_position());

			// Material

			shader.send_uniform("u_material", material);

			// Lights

			if (!scene_shader)
				shader.send_uniform("u_light", lights);

			// Texture

			if (textured)
			{
				shader.send_uniform("u_texture", texture);
				shader.send_uniform("u_textured", 1);
			}

			else
				shader.send_uniform("u_textured", 0);

			// Draw

			vertex_buffer.draw(draw_type);

			// Unbind

			if (!binded)
			{
				vertex_buffer.unbind();
				texture.unbind();
				shader.unbind();
			}
		}
	}

	Object::Object()
	{
		shader = Shader::get("default");
		vertex_buffer.set_shader(shader);
		vertex_buffer.send_data(this->mesh);
		scaling_matrix = glm::mat4(1.f);
		rotation_matrix = glm::mat4(1.f);
		translation_matrix = glm::mat4(1.f);
		origin_matrix = glm::mat4(1.f);
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
		binded = false;
		textured = false;
	}

	Object::Object(const Mesh& mesh, const Material& material)
	{
		shader = Shader::get("default");
		this->mesh = mesh;
		this->material = material;
		vertex_buffer.set_shader(shader);
		vertex_buffer.send_data(this->mesh);
		scaling_matrix = glm::mat4(1.f);
		rotation_matrix = glm::mat4(1.f);
		translation_matrix = glm::mat4(1.f);
		origin_matrix = glm::mat4(1.f);
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
		binded = false;
		textured = false;
	}

	void Object::set_shader(const std::string shader_name)
	{
		shader = Shader::get(shader_name);
		vertex_buffer.set_shader(shader_name);
		vertex_buffer.send_data(mesh);
	}

	void Object::set_shader(Shader& shader)
	{
		this->shader = shader;
		vertex_buffer.set_shader(this->shader);
		vertex_buffer.send_data(mesh);
	}

	void Object::set_texture(const std::string texture_name)
	{
		texture = Texture::get(texture_name);
		textured = true;
	}

	void Object::set_texture(Texture& texture)
	{
		this->texture = texture;
		textured = true;
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
		shader.bind();
		texture.bind();
		vertex_buffer.bind();
		binded = true;
	}

	void Object::unbind()
	{
		vertex_buffer.unbind();
		texture.unbind();
		shader.unbind();
		binded = false;
	}
}
