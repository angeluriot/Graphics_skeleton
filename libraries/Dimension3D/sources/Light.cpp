#include "dim/dimension3D.h"

namespace dim
{
	Light::Light()
	{
		type = Type::Ambiant;
		vector = Vector3();
		color = sf::Color(0.f, 0.f, 0.f, 0.f);
		intensity = 1.f;
	}

	Light::Light(const Light& other)
	{
		*this = other;
	}

	Light::Light(Type type, const sf::Color& color, float intensity, const Vector3& vector)
	{
		this->type = type;
		this->vector = vector;

		this->color = color;
		this->color.r = this->color.r * (this->color.a / 255.f);
		this->color.g = this->color.g * (this->color.a / 255.f);
		this->color.b = this->color.b * (this->color.a / 255.f);
		this->color.a = 255;

		this->intensity = intensity;
	}

	Light::Type Light::get_type() const
	{
		return type;
	}

	void Light::set_type(Type type)
	{
		this->type = type;
	}

	Vector3 Light::get_vector() const
	{
		return vector;
	}

	void Light::set_vector(const Vector3& vector)
	{
		this->vector = vector;
	}

	sf::Color Light::get_color() const
	{
		return color;
	}

	void Light::set_color(const sf::Color& color)
	{
		this->color = color;
	}

	float Light::get_intensity() const
	{
		return intensity;
	}

	void Light::set_intensity(float intensity)
	{
		this->intensity = intensity;
	}

	void Light::operator=(const Light& other)
	{
		type = other.type;
		vector = other.vector;
		color = other.color;
		intensity = other.intensity;
	}
}
