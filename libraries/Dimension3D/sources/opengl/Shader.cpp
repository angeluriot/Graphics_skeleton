#include "dim/dimension3D.h"

namespace dim
{
	std::vector<Shader> Shader::shaders = {};

	void Shader::load_default()
	{
		Shader shader;
		shader.name = "default_colored";
		shader.valid = shader.ptr->loadFromMemory(
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

		shaders.push_back(shader);
	}

	Shader::Shader()
	{
		ptr = std::make_shared<sf::Shader>();
		name.clear();
		valid = false;
	}

	Shader::Shader(const Shader& other)
	{
		*this = other;
	}

	Shader::Shader(const std::string& name, const std::string& folder_path)
	{
		ptr = std::make_shared<sf::Shader>();
		load(name, folder_path);
	}

	Shader::Shader(const std::string& name, const std::string& vert_path, const std::string& frag_path)
	{
		ptr = std::make_shared<sf::Shader>();
		load(name, vert_path, frag_path);
	}

	Shader& Shader::operator=(const Shader& other)
	{
		ptr = other.ptr;
		name = other.name;
		valid = other.valid;

		return *this;
	}

	bool Shader::load(const std::string& name, const std::string& folder_path)
	{
		this->name = name;
		std::string slash = "";

		if (folder_path.back() != '/')
			slash = "/";

		valid = ptr->loadFromFile(folder_path + slash + this->name + ".vert", folder_path + slash + this->name + ".frag");
		return valid;
	}

	bool Shader::load(const std::string& name, const std::string& vert_path, const std::string& frag_path)
	{
		this->name = name;
		valid = ptr->loadFromFile(vert_path, frag_path);
		return valid;
	}

	GLuint Shader::get_id() const
	{
		return ptr->getNativeHandle();
	}

	bool Shader::is_valid() const
	{
		return valid;
	}

	void Shader::bind() const
	{
		glUseProgram(get_id());
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	bool Shader::add_shader(const Shader& shader)
	{
		if (std::any_of(shaders.begin(), shaders.end(), [&](Shader& i) -> bool { return i.name == shader.name; }) || !shader.is_valid())
			return false;

		shaders.push_back(shader);
		return true;
	}

	bool Shader::add_shader(const std::string& name, const std::string& folder_path)
	{
		if (std::any_of(shaders.begin(), shaders.end(), [&](Shader& i) -> bool { return i.name == name; }))
			return false;

		Shader shader(name, folder_path);

		if (!shader.is_valid())
			return false;

		shaders.push_back(shader);
		return true;
	}

	bool Shader::add_shader(const std::string& name, const std::string& vert_path, const std::string& frag_path)
	{
		if (std::any_of(shaders.begin(), shaders.end(), [&](Shader& i) -> bool { return i.name == name; }))
			return false;

		Shader shader(name, vert_path, frag_path);

		if (!shader.is_valid())
			return false;

		shaders.push_back(shader);
		return true;
	}

	Shader* Shader::get_shader(const std::string& name)
	{
		auto shader = std::find_if(shaders.begin(), shaders.end(), [&](Shader& i) -> bool { return i.name == name; });

		if (shader == shaders.end())
			return NULL;

		return &(*shader);
	}

	GLuint Shader::get_id(const std::string& name)
	{
		Shader* shader = get_shader(name);

		if (shader == NULL)
			return 0;

		return shader->get_id();
	}

	void Shader::clear()
	{
		shaders.clear();
	}
}
