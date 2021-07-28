#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "dim/utils/libraries.h"
#include "dim/opengl/Shader.h"
#include "dim/vectors/Vector2.h"
#include "dim/vectors/Vector3.h"
#include "dim/vectors/Vector4.h"
#include "dim/opengl/Texture.h"

namespace dim
{
	class Texture;
	class Object;
	void unbind_all();

	enum class DrawType { Triangles = GL_TRIANGLES, Lines = GL_LINES, Points = GL_POINTS };

	class VertexBuffer
	{
	private:

		const Shader*					shader;
		GLuint							vbo;
		GLuint							vao;
		uint32_t						nb_vertices;
		std::vector<Texture*>			textures;
		std::shared_ptr<bool>			nb_copies;

	public:

										VertexBuffer();
										VertexBuffer(const VertexBuffer& other);
										VertexBuffer(const std::string& shader_name);
										VertexBuffer(const Shader& shader);
										~VertexBuffer();

		VertexBuffer&					operator=(const VertexBuffer& other);

		bool							set_shader(const std::string& shader_name);
		void							set_shader(const Shader& shader);
		void							send_data(const Mesh& mesh);
		void							clear_textures();
		bool							add_texture(const std::string& texture_name);
		void							add_texture(Texture& texture);

		void							send_uniform(const std::string& name, float number) const;
		void							send_uniform(const std::string& name, int number) const;
		void							send_uniform(const std::string& name, unsigned int number) const;

		void							send_uniform(const std::string& name, const std::vector<float>& numbers) const;
		void							send_uniform(const std::string& name, const std::vector<int>& numbers) const;
		void							send_uniform(const std::string& name, const std::vector<unsigned int>& numbers) const;

		void							send_uniform_2(const std::string& name, const std::vector<float>& numbers) const;
		void							send_uniform_2(const std::string& name, const std::vector<int>& numbers) const;
		void							send_uniform_2(const std::string& name, const std::vector<unsigned int>& numbers) const;

		void							send_uniform_3(const std::string& name, const std::vector<float>& numbers) const;
		void							send_uniform_3(const std::string& name, const std::vector<int>& numbers) const;
		void							send_uniform_3(const std::string& name, const std::vector<unsigned int>& numbers) const;

		void							send_uniform_4(const std::string& name, const std::vector<float>& numbers) const;
		void							send_uniform_4(const std::string& name, const std::vector<int>& numbers) const;
		void							send_uniform_4(const std::string& name, const std::vector<unsigned int>& numbers) const;

		void							send_uniform(const std::string& name, const Vector2& vector) const;
		void							send_uniform(const std::string& name, const Vector3& vector) const;
		void							send_uniform(const std::string& name, const Vector4& vector) const;
		void							send_uniform(const std::string& name, const sf::Color& color) const;

		void							send_uniform(const std::string& name, const std::vector<Vector2>& vectors) const;
		void							send_uniform(const std::string& name, const std::vector<Vector3>& vectors) const;
		void							send_uniform(const std::string& name, const std::vector<Vector4>& vectors) const;
		void							send_uniform(const std::string& name, const std::vector<sf::Color>& colors) const;

		void							send_uniform(const std::string& name, const glm::mat2& matrix) const;
		void							send_uniform(const std::string& name, const glm::mat3& matrix) const;
		void							send_uniform(const std::string& name, const glm::mat4& matrix) const;

		void							bind() const;
		static void						unbind();
		void							draw(DrawType draw_type = DrawType::Triangles) const;

		friend							Object;
		friend void						unbind_all();
	};
}

#endif
