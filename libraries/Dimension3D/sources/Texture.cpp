#include "dim/dimension3D.h"

namespace dim
{
	std::vector<Texture> Texture::textures = {};
	std::vector<int64_t> Texture::current = {};

	void Texture::change_current(const std::vector<const Texture*>& textures)
	{
		std::vector<int64_t> textures_id;

		for (auto& texture : textures)
			textures_id.push_back(texture->id);

		if (current != textures_id)
		{
			for (auto& texture_id : current)
				glBindTexture(GL_TEXTURE_2D, 0);

			uint16_t index = 0;
			current = textures_id;

			for (auto& texture_id : current)
			{
				glActiveTexture(GL_TEXTURE0 + index);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				index++;
			}
		}
	}

	void Texture::unbind()
	{
		for (auto& texture_id : current)
			glBindTexture(GL_TEXTURE_2D, 0);

		current = {};
	}

	Texture::Texture()
	{
		name.clear();
		id = 0;
		valid = false;
		nb_copies = std::make_shared<bool>();
	}

	Texture::Texture(const Texture& other)
	{
		*this = other;
	}

	Texture::Texture(const std::string& name, const std::string& path, Filtering filtering, Warpping warpping)
	{
		nb_copies = std::make_shared<bool>();
		load(name, path, filtering, warpping);
	}

	Texture::~Texture()
	{
		if (nb_copies.unique())
			glDeleteTextures(1, &id);
	}

	void Texture::operator=(const Texture& other)
	{
		name = other.name;
		id = other.id;
		valid = other.valid;
		nb_copies = other.nb_copies;
	}

	bool Texture::load(const std::string& name, const std::string& path, Filtering filtering, Warpping warpping)
	{
		this->name = name;
		sf::Image image;
		if (!image.loadFromFile(path))
		{
			valid = false;
			return false;
		}

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)filtering);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)filtering);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)warpping);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)warpping);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)image.getPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		valid = true;
		return true;
	}

	GLuint Texture::get_id() const
	{
		return id;
	}

	bool Texture::is_valid() const
	{
		return valid;
	}

	bool Texture::add_texture(const Texture& texture)
	{
		if (std::any_of(textures.begin(), textures.end(), [&](Texture& i) -> bool { return i.name == texture.name; }) || !texture.is_valid())
			return false;

		textures.push_back(texture);
		return true;
	}

	bool Texture::add_texture(const std::string& name, const std::string& path, Filtering filtering, Warpping warpping)
	{
		if (std::any_of(textures.begin(), textures.end(), [&](Texture& i) -> bool { return i.name == name; }))
			return false;

		Texture texture(name, path, filtering, warpping);

		if (!texture.is_valid())
			return false;

		textures.push_back(texture);
		return true;
	}

	Texture* Texture::get_texture(const std::string& name)
	{
		auto texture = std::find_if(textures.begin(), textures.end(), [&](Texture& i) -> bool { return i.name == name; });

		if (texture == textures.end())
			return NULL;

		return &(*texture);
	}

	GLuint Texture::get_id(const std::string& name)
	{
		Texture* texture = get_texture(name);

		if (texture == NULL)
			return 0;

		return texture->get_id();
	}

	void Texture::clear()
	{
		textures.clear();
	}
}
