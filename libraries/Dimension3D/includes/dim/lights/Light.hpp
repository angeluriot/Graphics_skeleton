#ifndef LIGHT_H
#define LIGHT_H

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/lights/Light.hpp"
#include "dim/utils/Color.hpp"

namespace dim
{
	class Light
	{
	public:

		enum class Type { Ambiant = 0, Directional = 1, Point = 2 };

	private:

		Type		type;
		Vector3		vector;
		Color		color;
		float		intensity;

	public:

					Light(const Light& other) = default;
					Light(Type type = Type::Ambiant, const Color& color = Color::White, float intensity = 1.f, const Vector3& vector = Vector3());

		Light&		operator=(const Light& other) = default;

		Type		get_type() const;
		void		set_type(Type type);
		Vector3		get_vector() const;
		void		set_vector(const Vector3& vector);
		Color		get_color() const;
		void		set_color(const Color& color);
		float		get_intensity() const;
		void		set_intensity(float intensity);
	};
}

#endif
