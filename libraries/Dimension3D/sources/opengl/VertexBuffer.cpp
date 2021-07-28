#include "dim/dimension3D.h"

namespace dim
{
	VertexBuffer::VertexBuffer()
	{
		shader = Shader::get_shader("default");
		vbo = 0;
		vao = 0;
		nb_vertices = 0;
		textures.clear();
		nb_copies = std::make_shared<bool>();
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& other)
	{
		*this = other;
	}

	VertexBuffer::VertexBuffer(const std::string& shader_name)
	{
		shader = Shader::get_shader(shader_name);
		vbo = 0;
		vao = 0;
		nb_vertices = 0;
		textures.clear();
		nb_copies = std::make_shared<bool>();
	}

	VertexBuffer::VertexBuffer(const Shader& shader)
	{
		this->shader = &shader;
		vbo = 0;
		vao = 0;
		nb_vertices = 0;
		textures.clear();
		nb_copies = std::make_shared<bool>();
	}

	VertexBuffer::~VertexBuffer()
	{
		if (nb_copies.unique())
		{
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}
	}

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
	{
		shader = other.shader;
		vbo = other.vbo;
		vao = other.vao;
		nb_vertices = other.nb_vertices;
		textures = other.textures;
		nb_copies = other.nb_copies;

		return *this;
	}

	// Toujours avant send_data

	bool VertexBuffer::set_shader(const std::string& shader_name)
	{
		Shader* s = Shader::get_shader(shader_name);

		if (s == NULL)
			return false;

		shader = s;
		return true;
	}

	void VertexBuffer::set_shader(const Shader& shader)
	{
		this->shader = &shader;
	}

	// Toujours apr�s set_shader

	void VertexBuffer::send_data(const Mesh& mesh)
	{
		if (nb_copies.unique())
		{
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}

		else
		{
			vbo = 0;
			vao = 0;
		}

		nb_vertices = 0;

		if (mesh.get_nb_vertices() > 0)
		{
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			{
				glBufferData(GL_ARRAY_BUFFER, mesh.get_data_size() * sizeof(float), NULL, GL_STATIC_DRAW);

				uint32_t data_i = 0;

				for (auto& vertex : mesh.vertex_array)
				{
					glBufferSubData(GL_ARRAY_BUFFER, data_i * sizeof(float), vertex.vertices.size() * sizeof(float), vertex.vertices.data());
					data_i += vertex.vertices.size();
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				{
					uint32_t data_i = 0;

					for (auto& vertex : mesh.vertex_array)
					{
						GLint data = glGetAttribLocation(shader->get_id(), vertex.name.data());
						glVertexAttribPointer(data, vertex.nb_dimensions, GL_FLOAT, GL_FALSE, vertex.nb_dimensions * sizeof(float), (GLvoid*)(data_i * sizeof(float)));
						glEnableVertexAttribArray(data);
						data_i += vertex.vertices.size();
					}
				}
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			glBindVertexArray(0);

			nb_vertices = mesh.get_nb_vertices();
		}
	}

	void VertexBuffer::clear_textures()
	{
		textures.clear();
	}

	bool VertexBuffer::add_texture(const std::string& texture_name)
	{
		Texture* t = Texture::get_texture(texture_name);

		if (t == NULL)
			return false;

		textures.push_back(t);
		return true;
	}

	void VertexBuffer::add_texture(Texture& texture)
	{
		textures.push_back(&texture);
	}

	void VertexBuffer::send_uniform(const std::string& name, float number) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1f(value, number);
	}

	void VertexBuffer::send_uniform(const std::string& name, int number) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1i(value, number);
	}

	void VertexBuffer::send_uniform(const std::string& name, unsigned int number) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1ui(value, number);
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<float>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1fv(value, numbers.size(), numbers.data());
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1iv(value, numbers.size(), numbers.data());
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<unsigned int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform1uiv(value, numbers.size(), numbers.data());
	}

	void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<float>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform2fv(value, numbers.size() / 2, numbers.data());
	}

	void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform2iv(value, numbers.size() / 2, numbers.data());
	}

	void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<unsigned int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform2uiv(value, numbers.size() / 2, numbers.data());
	}

	void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<float>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform3fv(value, numbers.size() / 3, numbers.data());
	}

	void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform3iv(value, numbers.size() / 3, numbers.data());
	}

	void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<unsigned int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform3uiv(value, numbers.size() / 3, numbers.data());
	}

	void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<float>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4fv(value, numbers.size() / 4, numbers.data());
	}

	void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4iv(value, numbers.size() / 4, numbers.data());
	}

	void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<unsigned int>& numbers) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4uiv(value, numbers.size() / 4, numbers.data());
	}

	void VertexBuffer::send_uniform(const std::string& name, const Vector2& vector) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform2f(value, vector.x, vector.y);
	}

	void VertexBuffer::send_uniform(const std::string& name, const Vector3& vector) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform3f(value, vector.x, vector.y, vector.z);
	}

	void VertexBuffer::send_uniform(const std::string& name, const Vector4& vector) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4f(value, vector.x, vector.y, vector.z, vector.w);
	}

	void VertexBuffer::send_uniform(const std::string& name, const sf::Color& color) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4f(value, color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<Vector2>& vectors) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform2fv(value, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<Vector3>& vectors) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform3fv(value, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<Vector4>& vectors) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4fv(value, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void VertexBuffer::send_uniform(const std::string& name, const std::vector<sf::Color>& colors) const
	{
		std::vector<Vector4> vectors;

		for (auto& color : colors)
			vectors.emplace_back(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);

		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniform4fv(value, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void VertexBuffer::send_uniform(const std::string& name, const glm::mat2& matrix) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniformMatrix2fv(value, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void VertexBuffer::send_uniform(const std::string& name, const glm::mat3& matrix) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniformMatrix3fv(value, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void VertexBuffer::send_uniform(const std::string& name, const glm::mat4& matrix) const
	{
		GLint value = glGetUniformLocation(shader->get_id(), name.data());
		glUniformMatrix4fv(value, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void VertexBuffer::bind() const
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexBuffer::draw(DrawType draw_type) const
	{
		for (uint16_t i = 0; i < textures.size(); i++)
		{
			GLint value = glGetUniformLocation(shader->get_id(), textures[i]->name.data());
			glUniform1i(value, i);
		}

		if (nb_vertices)
			glDrawArrays((GLenum)draw_type, 0, nb_vertices);
	}
}
