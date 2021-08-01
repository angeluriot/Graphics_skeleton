#ifndef COLOR_H
#define COLOR_H

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector4;

	class Color
	{
	public:

		float r;
		float g;
		float b;
		float a;

		static Color Transparent;
		static Color Black;
		static Color White;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Yellow;
		static Color Pink;
		static Color Cyan;
		static Color Orange;
		static Color Purple;
		static Color Grey;

		Color();
		Color(const Color& other) = default;
		Color(const Vector4& vector);
		Color(const sf::Color& color);
		Color(float red, float green, float blue, float alpha = 1.f);

		Color& operator=(const Color& other) = default;
		Color& operator=(const Vector4& vector);
		Color& operator=(const sf::Color& color);

		sf::Color to_sf() const;
	};
}

#endif
