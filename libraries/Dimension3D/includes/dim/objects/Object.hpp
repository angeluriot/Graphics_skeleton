#ifndef OBJECT_H
#define OBJECT_H

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/opengl/VertexBuffer.hpp"
#include "dim/objects/Material.hpp"
#include "dim/lights/Light.hpp"
#include "dim/opengl/Shader.hpp"
#include "dim/cameras/Camera.hpp"
#include "dim/windows/Scene.hpp"

namespace dim
{
	class Scene;
	class Window;
	class Shader;

	class Object
	{
	private:

		Shader			shader;
		VertexBuffer	vertex_buffer;
		Mesh			mesh;
		Texture			texture;
		glm::mat4		scaling_matrix;
		glm::mat4		rotation_matrix;
		glm::mat4		translation_matrix;
		glm::mat4		origin_matrix;
		glm::mat4		model;
		bool			binded;
		bool			textured;

		void			draw(const Camera* camera, const std::vector<Light>& lights, DrawType draw_type, bool scene_shader) const;

	public:

		Material		material;

						Object();
						Object(const Object& other) = default;
						Object(const Mesh& mesh, const Material& material = Material::default_material);

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

		friend			Scene;
		friend			Window;
	};
}

#endif
