#ifndef LIGHT_H
#define LIGHT_H

#include "dim/libraries.h"
#include "dim/Vector3.h"

namespace dim
{
	struct Light
	{
	public:

		enum class Type { Ambiant = 0, Directional = 1, Point = 2 };

	private:

		Type				type;
		Vector3				vector;
		sf::Color			color;
		float				intensity;

	public:

							Light();
							Light(const Light& other);
							Light(Type type, const sf::Color& color = sf::Color::White, float intensity = 1.f, const Vector3& vector = Vector3());

		void				operator=(const Light& other);

		Type				get_type() const;
		void				set_type(Type type);
		Vector3				get_vector() const;
		void				set_vector(const Vector3& vector);
		sf::Color			get_color() const;
		void				set_color(const sf::Color& color);
		float				get_intensity() const;
		void				set_intensity(float intensity);
	};
}

#endif
