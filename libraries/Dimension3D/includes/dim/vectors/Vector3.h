#ifndef VECTOR3_H
#define VECTOR3_H

#include "dim/utils/libraries.h"

namespace dim
{
	class Vector2;
	class Vector4;

	// Classe d�finissant un vecteur

	class Vector3
	{
	public:

		float					x;	// coordonn�e x
		float					y;	// coordonn�e y
		float					z;	// coordonn�e z

		static const Vector3	null;
		static const Vector3	unit;

								Vector3();
								Vector3(const Vector3& vector);
								Vector3(float x, float y, float z);
								Vector3(const Vector4& vector);
								Vector3(const Vector2& vector, float z);
								Vector3(float x, const Vector2& vector);
								Vector3(const std::array<float, 3>& vector);
								Vector3(const glm::vec3& vector);
								Vector3(const sf::Vector3f& vector);
								Vector3(const sf::Vector3i& vector);
								Vector3(const sf::Color& color);

		static Vector3			Cartesian(float x, float y, float z);
		static Vector3			Spherical(float norm, float theta, float phi);

		Vector3&				operator=(const Vector3& vector);
		Vector3&				operator=(float number);
		Vector3&				operator=(const std::array<float, 3>& vector);
		Vector3&				operator=(const glm::vec3& vector);
		Vector3&				operator=(const sf::Vector3f& vector);
		Vector3&				operator=(const sf::Vector3i& vector);
		Vector3&				operator=(const sf::Color& color);

		Vector3&				operator+=(const Vector3& vector);
		Vector3&				operator-=(const Vector3& vector);
		Vector3&				operator*=(const Vector3& vector);
		Vector3&				operator*=(float number);
		Vector3&				operator/=(const Vector3& vector);
		Vector3&				operator/=(float number);
		Vector3&				operator^=(const Vector3& vector);

		Vector3					operator+() const;
		Vector3					operator-() const;
		float					dot(const Vector3& vector) const;

		float					get_norm() const;
		float					get_norm_2() const;
		float					get_theta() const;
		float					get_phi() const;
		Vector3					get_normalized() const;
		const float*			get_ptr() const;

		float					get_distance(const Vector3& point) const;
		float					get_distance_2(const Vector3& point) const;
		float					get_theta(const Vector3& point) const;
		float					get_phi(const Vector3& point) const;

		void					set_norm(float norm);
		void					set_theta(float theta);
		void					set_phi(float phi);
		void					normalize();
		void					clear();

		std::array<float, 3>	to_array() const;
		glm::vec3				to_glm() const;
		sf::Vector3f			to_sf_float() const;
		sf::Vector3i			to_sf_int() const;
	};

	// Op�rateurs

	Vector3					operator+(const Vector3& vector_1, const Vector3& vector_2);
	Vector3					operator-(const Vector3& vector_1, const Vector3& vector_2);
	Vector3					operator*(float number, const Vector3& vector_2);
	Vector3					operator*(const Vector3& vector_1, float number);
	Vector3					operator*(const Vector3& vector_1, const Vector3& vector_2);
	Vector3					operator/(float number, const Vector3& vector_2);
	Vector3					operator/(const Vector3& vector, float number);
	Vector3					operator/(const Vector3& vector_1, const Vector3& vector_2);
	Vector3					operator^(const Vector3& vector_1, const Vector3& vector_2);
	float					dot(const Vector3& vector_1, const Vector3& vector_2);
	bool					operator==(const Vector3& vector_1, const Vector3& vector_2);
	bool					operator!=(const Vector3& vector_1, const Vector3& vector_2);
	std::ostream&			operator<<(std::ostream& os, const Vector3& vector);

	// R�cup�rer

	float					distance(const Vector3& point_1, const Vector3& point_2);
	float					distance_2(const Vector3& point_1, const Vector3& point_2);
	float					theta(const Vector3& point_1, const Vector3& point_2);
	float					phi(const Vector3& point_1, const Vector3& point_2);
	Vector3					normalized(const Vector3& vector);

	std::array<float, 3>	to_array(const Vector3& vector);
	glm::vec3				to_glm(const Vector3& vector);
	sf::Vector3f			to_sf_float(const Vector3& vector);
	sf::Vector3i			to_sf_int(const Vector3& vector);
}

#endif
