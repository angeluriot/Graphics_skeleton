#include "dim/dimension3D.h"

namespace dim
{
	Light::Light(Type type, const sf::Color& color, float intensity, const Vector3& vector)
	{
		set_type(type);
		set_color(color);
		set_intensity(intensity);
		set_vector(vector);
	}

	Light::Type Light::get_type() const
	{
		return type;
	}

	void Light::set_type(Type type)
	{
		if (type == Type::Directional)
			vector = normalized(-vector);

		this->type = type;
	}

	Vector3 Light::get_vector() const
	{
		return vector;
	}

	void Light::set_vector(const Vector3& vector)
	{
		if (type == Type::Directional)
			this->vector = normalized(vector);

		else
			this->vector = vector;
	}

	sf::Color Light::get_color() const
	{
		return color;
	}

	void Light::set_color(const sf::Color& color)
	{
		this->color.r = color.r * (color.a / 255.f);
		this->color.g = color.g * (color.a / 255.f);
		this->color.b = color.b * (color.a / 255.f);
		this->color.a = 255;
	}

	float Light::get_intensity() const
	{
		return intensity;
	}

	void Light::set_intensity(float intensity)
	{
		this->intensity = std::max(intensity, 0.f);
	}
}
