#include "dim/dimension3D.hpp"

// Construit un vecteur
namespace dim
{
	const Vector2 Vector2::null = Vector2();
	const Vector2 Vector2::unit = Vector2(1.f, 0.f);

	Vector2::Vector2()
	{
		x = 0.f;
		y = 0.f;
	}

	// Construit un vecteur à partir d'un autre vecteur

	Vector2::Vector2(const Vector2& vector)
	{
		*this = vector;
	}

	// Construit un vecteur à partir de ses coordonnées cartésiennes

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2(const Vector3& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	Vector2::Vector2(const Vector4& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector2::Vector2(const std::array<float, 2>& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector2::Vector2(const glm::vec2& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector2::Vector2(const sf::Vector2f& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector2::Vector2(const sf::Vector2i& vector)
	{
		*this = vector;
	}

	Vector2 Vector2::Cartesian(float x, float y)
	{
		return Vector2(x, y);
	}

	Vector2 Vector2::Polar(float norm, float angle)
	{
		return Vector2(cos(angle) * norm, sin(angle) * norm);
	}

	// Assignations

	Vector2& Vector2::operator=(const Vector2& vector)
	{
		x = vector.x;
		y = vector.y;

		return *this;
	}

	Vector2& Vector2::operator=(float number)
	{
		x = number;
		y = number;

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<float, 2>& vector)
	{
		x = vector[0];
		y = vector[1];

		return *this;
	}

	Vector2& Vector2::operator=(const glm::vec2& vector)
	{
		x = vector.x;
		y = vector.y;

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector2f& vector)
	{
		x = vector.x;
		y = vector.y;

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector2i& vector)
	{
		x = vector.x;
		y = vector.y;

		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& vector)
	{
		*this = *this + vector;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& vector)
	{
		*this = *this - vector;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& vector)
	{
		*this = *this * vector;
		return *this;
	}

	Vector2& Vector2::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& vector)
	{
		*this = *this / vector;
		return *this;
	}

	Vector2& Vector2::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector2 Vector2::operator+() const
	{
		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return null - *this;
	}

	float Vector2::dot(const Vector2& vector) const
	{
		return x * vector.x + y * vector.y;
	}

	// Donne la norme du vecteur

	float Vector2::get_norm() const
	{
		return sqrt(x * x + y * y);
	}

	// Donne la norme du vecteur au carr�

	float Vector2::get_norm_2() const
	{
		return x * x + y * y;
	}

	// Donne l'angle phi du vecteur

	float Vector2::get_angle() const
	{
		if (get_norm() == 0.f)
			return 0.f;

		if (y >= 0.f)
			return acos(x / get_norm());

		else
			return 2.f * pi - acos(x / get_norm());
	}

	Vector2 Vector2::get_normalized() const
	{
		if (get_norm() != 0.f)
			return *this / get_norm();

		return unit;
	}

	const float* Vector2::get_ptr() const
	{
		return &x;
	}

	float Vector2::get_distance(const Vector2& point) const
	{
		return (point - *this).get_norm();
	}

	float Vector2::get_distance_2(const Vector2& point) const
	{
		return (point - *this).get_norm_2();
	}

	float Vector2::get_angle(const Vector2& point) const
	{
		return (point - *this).get_angle();
	}

	// Modifie la norme du vecteur

	void Vector2::set_norm(float norm)
	{
		*this = get_normalized() * norm;
	}

	// Modifie l'angle theta du vecteur

	void Vector2::set_angle(float angle)
	{
		*this = Polar(get_norm(), angle);
	}

	// Normalise le vecteur

	void Vector2::normalize()
	{
		if (get_norm() != 0.f)
			*this /= get_norm();

		else
			*this = unit;
	}

	// Met toutes les composantes � z�ro

	void Vector2::clear()
	{
		*this = null;
	}

	std::array<float, 2> Vector2::to_array() const
	{
		return { x, y };
	}

	glm::vec2 Vector2::to_glm() const
	{
		return glm::vec2(x, y);
	}

	sf::Vector2f Vector2::to_sf_float() const
	{
		return sf::Vector2f(x, y);
	}

	sf::Vector2i Vector2::to_sf_int() const
	{
		return sf::Vector2i(x, y);
	}

	// Addition

	Vector2 operator+(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
	}

	// Soustraction

	Vector2 operator-(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
	}

	// Produits

	Vector2 operator*(float number, const Vector2& vector)
	{
		return Vector2(number * vector.x, number * vector.y);
	}

	Vector2 operator*(const Vector2& vector, float number)
	{
		return Vector2(vector.x * number, vector.y * number);
	}

	Vector2 operator*(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x * vector_2.x, vector_1.y * vector_2.y);
	}

	// Division

	Vector2 operator/(float number, const Vector2& vector)
	{
		return Vector2((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f));
	}

	Vector2 operator/(const Vector2& vector, float number)
	{
		if (number == 0.f)
			return Vector2::null;

		return Vector2(vector.x / number, vector.y / number);
	}

	Vector2 operator/(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f));
	}

	float dot(const Vector2& vector_1, const Vector2& vector_2)
	{
		return vector_1.dot(vector_2);
	}

	// Egalit�s

	bool operator==(const Vector2& vector_1, const Vector2& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y);
	}

	bool operator!=(const Vector2& vector_1, const Vector2& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	// Affichage

	std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	float distance(const Vector2& point_1, const Vector2& point_2)
	{
		return point_1.get_distance(point_2);
	}

	float distance_2(const Vector2& point_1, const Vector2& point_2)
	{
		return point_1.get_distance_2(point_2);
	}

	float angle(const Vector2& point_1, const Vector2& point_2)
	{
		return point_1.get_angle(point_2);
	}

	Vector2 normalized(const Vector2& vector)
	{
		return vector.get_normalized();
	}

	std::array<float, 2> to_array(const Vector2& vector)
	{
		return vector.to_array();
	}

	glm::vec2 to_glm(const Vector2& vector)
	{
		return vector.to_glm();
	}

	sf::Vector2f to_sf_float(const Vector2& vector)
	{
		return vector.to_sf_float();
	}

	sf::Vector2i to_sf_int(const Vector2& vector)
	{
		return vector.to_sf_int();
	}
}
