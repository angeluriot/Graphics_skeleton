#include "dim/dimension3D.hpp"

namespace dim
{
	Light* DirectionalLight::clone() const
	{
		return new DirectionalLight(*this);
	}

	DirectionalLight::DirectionalLight(const Vector3& direction, const Color& color, float intensity)
	{
		set_direction(direction);
		set_color(color);
		set_intensity(intensity);
	}

	void DirectionalLight::set_direction(const Vector3& direction)
	{
		vector = normalized(direction);
	}

	Vector3 DirectionalLight::get_direction() const
	{
		return vector;
	}

	Light::Type DirectionalLight::get_type() const
	{
		return Type::Directional;
	}
}
