#include "dim/Dimension3D.hpp"

namespace dim
{
	Color Color::Transparent = Color(0, 0, 0, 0);
	Color Color::Black = Color(0, 0, 0, 1);
	Color Color::White = Color(1, 1, 1, 1);
	Color Color::Red = Color(1, 0, 0, 1);
	Color Color::Green = Color(0, 1, 0, 1);
	Color Color::Blue = Color(0, 0, 1, 1);
	Color Color::Yellow = Color(1, 1, 0, 1);
	Color Color::Pink = Color(1, 0, 1, 1);
	Color Color::Cyan = Color(0, 1, 1, 1);
	Color Color::Orange = Color(1, 0.5, 0, 1);
	Color Color::Purple = Color(0.5, 0, 1, 1);
	Color Color::Grey = Color(0.5, 0.5, 0.5, 1);

	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color::Color(const Vector4& vector)
	{
		*this = vector;
	}

	Color::Color(const sf::Color& color)
	{
		*this = color;
	}

	Color::Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color& Color::operator=(const Vector4& vector)
	{
		r = vector.x;
		g = vector.y;
		b = vector.z;
		a = vector.w;

		return *this;
	}

	Color& Color::operator=(const sf::Color& color)
	{
		r = color.r / 255.f;
		g = color.g / 255.f;
		b = color.b / 255.f;
		a = color.a / 255.f;

		return *this;
	}

	sf::Color Color::to_sf() const
	{
		return sf::Color(r * 255, g * 255, b * 255, a * 255);
	}
}
