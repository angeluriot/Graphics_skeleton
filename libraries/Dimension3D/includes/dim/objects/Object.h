#ifndef OBJECT_H
#define OBJECT_H

#include "dim/utils/libraries.h"
#include "dim/vectors/Vector3.h"
#include "dim/opengl/VertexBuffer.h"
#include "dim/utils/Material.h"
#include "dim/objects/Light.h"
#include "dim/opengl/Shader.h"
#include "dim/objects/Camera.h"
#include "dim/windows/Scene.h"

namespace dim
{
	class Object
	{
	private:

		VertexBuffer	vertex_buffer;
		Mesh			mesh;
		glm::mat4		scaling_matrix;
		glm::mat4		rotation_matrix;
		glm::mat4		translation_matrix;
		glm::mat4		origin_matrix;
		glm::mat4		model;
		bool			binded;

	public:

		Material		material;

						Object(const Object& other) = default;
						Object(const Mesh& mesh = Mesh::null, const Material& material = Material::default_material);

		Object&			operator=(const Object& other) = default;

		void			set_shader(const std::string shader_name);
		void			set_shader(Shader& shader);
		void			set_texture(const std::string texture_name);
		void			set_texture(Texture& texture);
		void			set_mesh(const Mesh& mesh);

		void			set_size(const Vector3& new_size);
		void			set_rotation(float new_rotation, const Vector3& new_axis);
		void			set_position(const Vector3& new_position);
		void			set_origin(const Vector3& new_origin);

		void			scale(const Vector3& scale);
		void			rotate(float rotation, const Vector3& axis);
		void			move(const Vector3& movement);

		Vector3			get_size() const;
		glm::mat4		get_rotation() const;
		Vector3			get_position() const;
		Vector3			get_origin() const;

		void			bind();
		void			unbind();
		void			draw(const Scene& scene = Scene::window, const Camera& camera = Camera::null, const std::vector<Light>& lights = {}, DrawType draw_type = DrawType::Triangles) const;
	};
}

#endif
