#ifndef OBJECT_H
#define OBJECT_H

#include "dim/libraries.h"
#include "dim/Vector3.h"
#include "dim/VertexBuffer.h"
#include "dim/Material.h"
#include "dim/Light.h"
#include "dim/Shader.h"
#include "dim/Camera.h"

namespace dim
{
	class Object
	{
	private:

		VertexBuffer					vertex_object;
		Mesh						mesh;
		Material						material;
		glm::mat4						local_scale;
		glm::mat4						local_rotation;
		glm::mat4						local_position;
		glm::mat4						local_matrix;
		glm::mat4						propagated_scale;
		glm::mat4						propagated_rotation;
		glm::mat4						propagated_position;
		glm::mat4						propagated_matrix;
		glm::mat4						parent_matrix;
		glm::mat4						model;
		Object*							parent;
		std::vector<Object*>			children;

		void							update_model(const glm::mat4& parent_matrix);

	public:

										Object();
										Object(const Object& other);
										Object(const Mesh& mesh, const Material& material = Material::default_material);

		Object&							operator=(const Object& other);

		bool							set_shader(const std::string shader_name);
		void							set_shader(Shader& shader);
		bool							set_texture(const std::string texture_name);
		void							set_texture(Texture& texture);
		void							set_geometry(const Mesh& mesh);
		void							set_material(const Material& material);
		void							add_child(Object& child);

		void							set_local_scale(const Vector3& new_scale);
		void							set_local_rotation(float new_rotation, const Vector3& new_axis);
		void							set_local_position(const Vector3& new_position);

		void							scale_local(const Vector3& scale);
		void							rotate_local(float rotation, const Vector3& axis);
		void							move_local(const Vector3& movement);

		void							set_scale(const Vector3& new_scale);
		void							set_rotation(float new_rotation, const Vector3& new_axis);
		void							set_position(const Vector3& new_position);

		void							scale(const Vector3& scale);
		void							rotate(float rotation, const Vector3& axis);
		void							move(const Vector3& movement);

		Material						get_material() const;

		Vector3							get_local_scale() const;
		glm::mat4						get_local_rotation() const;
		Vector3							get_local_position() const;

		Vector3							get_scale() const;
		glm::mat4						get_rotation() const;
		Vector3							get_position() const;

		void							draw(const Camera& camera, const std::vector<Light*>& lights, DrawType draw_type = DrawType::Triangles) const;
	};
}

#endif
