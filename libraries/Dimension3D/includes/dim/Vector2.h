#ifndef VECTOR2_H
#define VECTOR2_H

#include "dim/libraries.h"

namespace dim
{
	class Vector3;
	class Vector4;

	// Classe d�finissant un vecteur

	class Vector2
	{
	public:

		float					x;	// coordonn�e x
		float					y;	// coordonn�e y

		static const Vector2	null;
		static const Vector2	unit;

								Vector2();
								Vector2(const Vector2& vector);
								Vector2(float x, float y);
								Vector2(const Vector3& vector);
								Vector2(const Vector4& vector);
								Vector2(const std::array<float, 2>& vector);
								Vector2(const glm::vec2& vector);
								Vector2(const sf::Vector2f& vector);
								Vector2(const sf::Vector2i& vector);

		static Vector2			Cartesian(float x, float y);
		static Vector2			Polar(float norm, float angle);

		Vector2&				operator=(const Vector2& vector);
		Vector2&				operator=(float number);
		Vector2&				operator=(const std::array<float, 2>& vector);
		Vector2&				operator=(const glm::vec2& vector);
		Vector2&				operator=(const sf::Vector2f& vector);
		Vector2&				operator=(const sf::Vector2i& vector);

		Vector2&				operator+=(const Vector2& vector);
		Vector2&				operator-=(const Vector2& vector);
		Vector2&				operator*=(const Vector2& vector);
		Vector2&				operator*=(float number);
		Vector2&				operator/=(const Vector2& vector);
		Vector2&				operator/=(float number);

		Vector2					operator+() const;
		Vector2					operator-() const;
		float					dot(const Vector2& vector) const;

		float					get_norm() const;
		float					get_norm_2() const;
		float					get_angle() const;
		Vector2					get_normalized() const;
		const float*			get_ptr() const;

		float					get_distance(const Vector2& point) const;
		float					get_distance_2(const Vector2& point) const;
		float					get_angle(const Vector2& point) const;

		void					set_norm(float norm);
		void					set_angle(float angle);
		void					normalize();
		void					clear();

		std::array<float, 2>	to_array() const;
		glm::vec2				to_glm() const;
		sf::Vector2f			to_sf_float() const;
		sf::Vector2i			to_sf_int() const;
	};

	// Op�rateurs

	Vector2					operator+(const Vector2& vector_1, const Vector2& vector_2);
	Vector2					operator-(const Vector2& vector_1, const Vector2& vector_2);
	Vector2					operator*(float number, const Vector2& vector_2);
	Vector2					operator*(const Vector2& vector_1, float number);
	Vector2					operator*(const Vector2& vector_1, const Vector2& vector_2);
	Vector2					operator/(float number, const Vector2& vector_2);
	Vector2					operator/(const Vector2& vector, float number);
	Vector2					operator/(const Vector2& vector_1, const Vector2& vector_2);
	float					dot(const Vector2& vector_1, const Vector2& vector_2);
	bool					operator==(const Vector2& vector_1, const Vector2& vector_2);
	bool					operator!=(const Vector2& vector_1, const Vector2& vector_2);
	std::ostream&			operator<<(std::ostream& os, const Vector2& vector);

	// R�cup�rer

	float					distance(const Vector2& point_1, const Vector2& point_2);
	float					distance_2(const Vector2& point_1, const Vector2& point_2);
	float					angle(const Vector2& point_1, const Vector2& point_2);
	Vector2					normalized(const Vector2& vector);

	std::array<float, 2>	to_array(const Vector2& vector);
	glm::vec2				to_glm(const Vector2& vector);
	sf::Vector2f			to_sf_float(const Vector2& vector);
	sf::Vector2i			to_sf_int(const Vector2& vector);
}

#endif
