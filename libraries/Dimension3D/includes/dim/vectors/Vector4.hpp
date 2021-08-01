#ifndef VECTOR4_H
#define VECTOR4_H

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector3;
	class Color;

	// Classe d�finissant un vecteur

	class Vector4
	{
	public:

		float					x;	// coordonn�e x
		float					y;	// coordonn�e y
		float					z;	// coordonn�e z
		float					w;	// coordonn�e w

		static const Vector4	null;
		static const Vector4	unit;

								Vector4();
								Vector4(const Vector4& vector);
								Vector4(float x, float y, float z, float w);
								Vector4(const Vector2& vector, float z, float w);
								Vector4(float x, const Vector2& vector, float w);
								Vector4(float x, float y, const Vector2& vector);
								Vector4(const Vector3& vector, float w);
								Vector4(float x, const Vector3& vector);
								Vector4(const std::array<float, 4>& vector);
								Vector4(const glm::vec4& vector);
								Vector4(const Color& color);

		Vector4&				operator=(const Vector4& vector);
		Vector4&				operator=(float number);
		Vector4&				operator=(const std::array<float, 4>& vector);
		Vector4&				operator=(const glm::vec4& vector);
		Vector4&				operator=(const Color& color);

		Vector4&				operator+=(const Vector4& vector);
		Vector4&				operator-=(const Vector4& vector);
		Vector4&				operator*=(const Vector4& vector);
		Vector4&				operator*=(float number);
		Vector4&				operator/=(const Vector4& vector);
		Vector4&				operator/=(float number);

		Vector4					operator+() const;
		Vector4					operator-() const;
		float					dot(const Vector4& vector) const;

		float					get_norm() const;
		float					get_norm_2() const;
		Vector4					get_normalized() const;
		const float*			get_ptr() const;

		float					get_distance(const Vector4& point) const;
		float					get_distance_2(const Vector4& point) const;

		void					set_norm(float norm);
		void					normalize();
		void					clear();

		std::array<float, 4>	to_array() const;
		glm::vec4				to_glm() const;
	};

	// Op�rateurs

	Vector4					operator+(const Vector4& vector_1, const Vector4& vector_2);
	Vector4					operator-(const Vector4& vector_1, const Vector4& vector_2);
	Vector4					operator*(float number, const Vector4& vector_2);
	Vector4					operator*(const Vector4& vector_1, float number);
	Vector4					operator*(const Vector4& vector_1, const Vector4& vector_2);
	Vector4					operator/(float number, const Vector4& vector_2);
	Vector4					operator/(const Vector4& vector, float number);
	Vector4					operator/(const Vector4& vector_1, const Vector4& vector_2);
	float					dot(const Vector4& vector_1, const Vector4& vector_2);

	bool					operator==(const Vector4& vector_1, const Vector4& vector_2);
	bool					operator!=(const Vector4& vector_1, const Vector4& vector_2);
	std::ostream&			operator<<(std::ostream& os, const Vector4& vector);

	// R�cup�rer

	float					distance(const Vector4& point_1, const Vector4& point_2);
	float					distance_2(const Vector4& point_1, const Vector4& point_2);
	Vector4					normalized(const Vector4& vector);

	std::array<float, 4>	to_array(const Vector4& vector);
	glm::vec4				to_glm(const Vector4& vector);
}

#endif
