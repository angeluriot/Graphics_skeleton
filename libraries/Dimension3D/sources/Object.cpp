#include "dim/dimension3D.h"

namespace dim
{
	void Object::update_model(const glm::mat4& parent_matrix)
	{
		this->parent_matrix = parent_matrix;
		model = this->parent_matrix * propagated_matrix * local_matrix;
		glm::mat4 child_matrix = this->parent_matrix * propagated_matrix;

		for (auto& child : children)
			child->update_model(child_matrix);
	}

	Object::Object()
	{
		local_scale = glm::mat4(1.f);
		local_rotation = glm::mat4(1.f);
		local_position = glm::mat4(1.f);
		local_matrix = local_position * local_rotation * local_scale;
		propagated_scale = glm::mat4(1.f);
		propagated_rotation = glm::mat4(1.f);
		propagated_position = glm::mat4(1.f);
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;
		parent_matrix = glm::mat4(1.f);
		model = propagated_matrix * local_matrix;
		parent = NULL;
		children.clear();
	}

	Object::Object(const Object& other)
	{
		*this = other;
	}

	Object::Object(const Mesh& mesh, const Material& material)
	{
		vertex_object.set_shader("default");
		vertex_object.send_data(mesh);
		this->mesh = mesh;
		this->material = material;
		local_scale = glm::mat4(1.f);
		local_rotation = glm::mat4(1.f);
		local_position = glm::mat4(1.f);
		local_matrix = local_position * local_rotation * local_scale;
		propagated_scale = glm::mat4(1.f);
		propagated_rotation = glm::mat4(1.f);
		propagated_position = glm::mat4(1.f);
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;
		parent_matrix = glm::mat4(1.f);
		model = propagated_matrix * local_matrix;
		parent = NULL;
		children.clear();
	}

	Object& Object::operator=(const Object& other)
	{
		vertex_object = other.vertex_object;
		mesh = other.mesh;
		material = other.material;
		local_scale = other.local_scale;
		local_rotation = other.local_rotation;
		local_position = other.local_position;
		local_matrix = other.local_matrix;
		propagated_scale = other.propagated_scale;
		propagated_rotation = other.propagated_rotation;
		propagated_position = other.propagated_position;
		propagated_matrix = other.propagated_matrix;
		parent_matrix = other.parent_matrix;
		model = other.model;
		parent = other.parent;
		children = other.children;

		vertex_object.nb_copies = std::make_shared<bool>();
		vertex_object.send_data(mesh);

		return *this;
	}

	bool Object::set_shader(const std::string shader_name)
	{
		bool value = vertex_object.set_shader(shader_name);

		if (value)
		{
			vertex_object.send_data(mesh);
			return true;
		}

		return false;
	}

	void Object::set_shader(Shader& shader)
	{
		vertex_object.set_shader(shader);
		vertex_object.send_data(mesh);
	}

	bool Object::set_texture(const std::string texture_name)
	{
		bool value = vertex_object.add_texture(texture_name);

		if (value)
		{
			vertex_object.textures.clear();
			vertex_object.add_texture(texture_name);
			return true;
		}

		return false;
	}

	void Object::set_texture(Texture& texture)
	{
		vertex_object.textures.clear();
		vertex_object.add_texture(texture);
	}

	void Object::set_geometry(const Mesh& mesh)
	{
		this->mesh = mesh;
		vertex_object.send_data(mesh);
	}

	void Object::set_material(const Material& material)
	{
		this->material = material;
	}

	// TODO : Changer le parent et enlever celui d'avant

	void Object::add_child(Object& child)
	{
		if (child.parent != NULL)
			for (auto it = child.parent->children.begin(); it != child.parent->children.end(); it++)
				if ((*it) == &child)
				{
					child.parent->children.erase(it);
					break;
				}

		child.parent = this;
		update_model(parent_matrix);

		child.propagated_matrix = glm::inverse(parent_matrix * propagated_matrix) * child.propagated_matrix;
		children.push_back(&child);
	}

	void Object::set_local_scale(const Vector3& new_scale)
	{
		local_scale = glm::scale(glm::mat4(1.f), new_scale.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::set_local_rotation(float new_rotation, const Vector3& new_axis)
	{
		local_rotation = glm::rotate(glm::mat4(1.f), new_rotation, new_axis.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::set_local_position(const Vector3& new_position)
	{
		local_position = glm::translate(glm::mat4(1.f), new_position.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::scale_local(const Vector3& scale)
	{
		local_scale = glm::scale(local_scale, scale.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::rotate_local(float rotation, const Vector3& axis)
	{
		local_rotation = glm::rotate(local_rotation, rotation, axis.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::move_local(const Vector3& movement)
	{
		local_position = glm::translate(local_position, movement.to_glm());
		local_matrix = local_position * local_rotation * local_scale;
		model = propagated_matrix * local_matrix;
	}

	void Object::set_scale(const Vector3& new_scale)
	{
		propagated_scale = glm::scale(glm::mat4(1.f), new_scale.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	void Object::set_rotation(float new_rotation, const Vector3& new_axis)
	{
		propagated_rotation = glm::rotate(glm::mat4(1.f), new_rotation, new_axis.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	void Object::set_position(const Vector3& new_position)
	{
		propagated_position = glm::translate(glm::mat4(1.f), new_position.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	void Object::scale(const Vector3& scale)
	{
		propagated_scale = glm::scale(propagated_scale, scale.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	void Object::rotate(float rotation, const Vector3& axis)
	{
		propagated_rotation = glm::rotate(propagated_rotation, rotation, axis.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	void Object::move(const Vector3& movement)
	{
		propagated_position = glm::translate(propagated_position, movement.to_glm());
		propagated_matrix = propagated_position * propagated_rotation * propagated_scale;

		update_model(parent_matrix);
	}

	Material Object::get_material() const
	{
		return material;
	}

	Vector3 Object::get_local_scale() const
	{
		return Vector4(local_scale * glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	glm::mat4 Object::get_local_rotation() const
	{
		return local_rotation;
	}

	Vector3 Object::get_local_position() const
	{
		return Vector4(local_position * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	Vector3 Object::get_scale() const
	{
		return Vector4(propagated_scale * glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	glm::mat4 Object::get_rotation() const
	{
		return propagated_rotation;
	}

	Vector3 Object::get_position() const
	{
		return Vector4(propagated_position * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	// ATTENTION 10 LIGHTS MAX

	void Object::draw(const Camera& camera, const std::vector<Light*>& lights, DrawType draw_type) const
	{
		if (vertex_object.nb_vertices)
		{
			vertex_object.change_current({ vertex_object.vbo, vertex_object.vao });

			// Matrices

			vertex_object.send_uniform("u_model", model);
			vertex_object.send_uniform("u_inverted_model", glm::transpose(glm::inverse(glm::mat3(model))));
			vertex_object.send_uniform("u_mvp", camera.get_mvp() * model);

			// Camera

			vertex_object.send_uniform("u_camera", camera.get_position());

			// Materiaux

			vertex_object.send_uniform("u_color", material.get_color());
			vertex_object.send_uniform("u_ambient", material.get_ambient());
			vertex_object.send_uniform("u_diffuse", material.get_diffuse());
			vertex_object.send_uniform("u_specular", material.get_specular());
			vertex_object.send_uniform("u_shininess", material.get_shininess());

			// Lumi�re

			std::vector<int> light_types;
			std::vector<Vector3> light_vectors;
			std::vector<sf::Color> light_colors;
			std::vector<float> light_intensities;

			for (auto& light : lights)
			{
				light_types.push_back((int)light->get_type());
				light_vectors.push_back(light->get_vector());
				light_colors.push_back(light->get_color());
				light_intensities.push_back(light->get_intensity());
			}

			vertex_object.send_uniform("u_light_types", light_types);
			vertex_object.send_uniform("u_light_vectors", light_vectors);
			vertex_object.send_uniform("u_light_colors", light_colors);
			vertex_object.send_uniform("u_light_intensities", light_intensities);

			vertex_object.send_uniform("u_nb_lights", (int)lights.size());

			// Textures
			if (vertex_object.textures.size())
			{
				GLint u_texture = glGetUniformLocation(vertex_object.shader->get_id(), "u_texture");
				glUniform1i(u_texture, 0);

				vertex_object.send_uniform("u_textured", 1);
			}

			else
				vertex_object.send_uniform("u_textured", 0);

			glDrawArrays((GLenum)draw_type, 0, vertex_object.nb_vertices);
		}
	}
}
