#include "dim/dimension3D.hpp"

namespace dim
{
	std::map<std::string, Shader> Shader::shaders = {};
	Shader Shader::default_shader;

	void Shader::init()
	{
		default_shader.shader = std::make_shared<sf::Shader>();

		default_shader.shader->loadFromMemory(
			"#version 140\n"
			"precision mediump float;\n"
			"\n"
			"attribute vec3 positions;\n"
			"attribute vec3 normals;\n"
			"attribute vec2 uvs;\n"
			"\n"
			"varying vec3 v_normals;\n"
			"varying vec2 v_uvs;\n"
			"\n"
			"uniform mat4 u_model;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = u_model * vec4(positions, 1.);\n"
			"	v_normals = normals;\n"
			"	v_uvs = uvs;\n"
			"}",

			"#version 140\n"
			"precision mediump float;\n"
			"\n"
			"varying vec3 v_normals;\n"
			"varying vec2 v_uvs;\n"
			"\n"
			"uniform sampler2D texture_1;\n"
			"uniform sampler2D texture_2;\n"
			"\n"
			"uniform vec4 u_color;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_FragColor = u_color;\n"
			"	//gl_FragColor = vec4(texture2D(texture_2, v_uvs).rgb, 1.);\n"
			"}");
	}

	Shader::Shader() {}

	Shader::Shader(const std::string& vert_path, const std::string& frag_path)
	{
		shader = std::make_shared<sf::Shader>();
		load(vert_path, frag_path);
	}

	void Shader::load(const std::string& vert_path, const std::string& frag_path)
	{
		shader = std::make_shared<sf::Shader>();

		if (!shader->loadFromFile(vert_path, frag_path))
			throw std::runtime_error("The shader " + vert_path + " or " + frag_path + " could not be loaded");
	}

	GLuint Shader::get_id() const
	{
		return shader->getNativeHandle();
	}

	void Shader::bind() const
	{
		glUseProgram(get_id());
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	void Shader::send_uniform(const std::string& name, const Texture& texture) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1i(location, texture.get_unit());
	}

	void Shader::send_uniform(const std::string& name, const Light& light) const
	{
		send_uniform(name + ".type", (int)light.get_type());
		send_uniform(name + ".vector", light.get_vector());
		send_uniform(name + ".color", light.get_color());
		send_uniform(name + ".intensity", light.get_intensity());
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Light>& lights) const
	{
		std::vector<int> light_types;
		std::vector<Vector3> light_vectors;
		std::vector<Color> light_colors;
		std::vector<float> light_intensities;

		for (auto& light : lights)
		{
			light_types.push_back(static_cast<int>(light.get_type()));
			light_vectors.push_back(light.get_vector());
			light_colors.push_back(light.get_color());
			light_intensities.push_back(light.get_intensity());
		}

		send_uniform("u_light_types", light_types);
		send_uniform("u_light_vectors", light_vectors);
		send_uniform("u_light_colors", light_colors);
		send_uniform("u_light_intensities", light_intensities);
		send_uniform("u_nb_lights", static_cast<int>(lights.size()));
	}

	void Shader::send_uniform(const std::string& name, const Material& material) const
	{
		send_uniform(name + ".color", material.get_color());
		send_uniform(name + ".ambient", material.get_ambient());
		send_uniform(name + ".diffuse", material.get_diffuse());
		send_uniform(name + ".specular", material.get_specular());
		send_uniform(name + ".shininess", material.get_shininess());
	}

	void Shader::send_uniform(const std::string& name, float number) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1f(location, number);
	}

	void Shader::send_uniform(const std::string& name, int number) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1i(location, number);
	}

	void Shader::send_uniform(const std::string& name, const std::vector<float>& numbers, unsigned int group) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());

		if (group == 1)
			glUniform1fv(location, numbers.size(), numbers.data());

		else if (group == 2)
			glUniform2fv(location, numbers.size() / 2, numbers.data());

		else if (group == 3)
			glUniform3fv(location, numbers.size() / 3, numbers.data());

		else if (group == 4)
			glUniform4fv(location, numbers.size() / 4, numbers.data());

		else
			throw std::invalid_argument("Invalid group (<1 or >4)");
	}

	void Shader::send_uniform(const std::string& name, const std::vector<int>& numbers, unsigned int group) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());

		if (group == 1)
			glUniform1iv(location, numbers.size(), numbers.data());

		else if (group == 2)
			glUniform2iv(location, numbers.size() / 2, numbers.data());

		else if (group == 3)
			glUniform3iv(location, numbers.size() / 3, numbers.data());

		else if (group == 4)
			glUniform4iv(location, numbers.size() / 4, numbers.data());

		else
			throw std::invalid_argument("Invalid group (<1 or >4)");
	}

	void Shader::send_uniform(const std::string& name, const Vector2& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::send_uniform(const std::string& name, const Vector3& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::send_uniform(const std::string& name, const Vector4& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::send_uniform(const std::string& name, const Color& color) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4f(location, color.r, color.g, color.b, color.a);
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector2>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform2fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector3>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform3fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector4>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Color>& colors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4fv(location, colors.size(), reinterpret_cast<const float*>(colors.data()));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat2& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::add(const std::string& name, const Shader& shader)
	{
		if (!shaders.insert(std::make_pair(name, shader)).second)
			throw std::invalid_argument("This name is already used");
	}

	void Shader::add(const std::string& name, const std::string& vert_path, const std::string& frag_path)
	{
		if (!shaders.insert(std::make_pair(name, Shader(vert_path, frag_path))).second)
			throw std::invalid_argument("This name is already used");
	}

	void Shader::remove(const std::string& name)
	{
		if (!shaders.erase(name))
			throw std::invalid_argument("This name does not exit");
	}

	Shader Shader::get(const std::string& name)
	{
		try
		{
			return shaders.at(name);
		}

		catch (const std::out_of_range& e)
		{
			throw std::invalid_argument("This name does not exit");
		}
	}
}
