#include "dim/dimension3D.hpp"

namespace dim
{
	Material Material::default_material = Material(Color(1.f, 1.f, 1.f, 1.f), 0.4f, 0.6f, 0.4f, 50.f);

	Material::Material()
	{
		color = Color(0.f, 0.f, 0.f, 0.f);
		ambient = 0.f;
		diffuse = 0.f;
		specular = 0.f;
		shininess = 1.f;
	}

	Material::Material(const Color& color, float ambient, float diffuse, float specular, float shininess)
	{
		this->color = color;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}

	Color Material::get_color() const
	{
		return color;
	}

	void Material::set_color(const Color& color)
	{
		this->color = color;
	}

	float Material::get_ambient() const
	{
		return ambient;
	}

	void Material::set_ambient(float ambient)
	{
		this->ambient = ambient;
	}

	float Material::get_diffuse() const
	{
		return diffuse;
	}

	void Material::set_diffuse(float diffuse)
	{
		this->diffuse = diffuse;
	}

	float Material::get_specular() const
	{
		return specular;
	}

	void Material::set_specular(float specular)
	{
		this->specular = specular;
	}

	float Material::get_shininess() const
	{
		return shininess;
	}

	void Material::set_shininess(float shininess)
	{
		this->shininess = shininess;
	}
}
