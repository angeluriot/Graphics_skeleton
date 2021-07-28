#include "dim/dimension3D.h"

// Construit un vecteur
namespace dim
{
	const Vector4 Vector4::null = Vector4();
	const Vector4 Vector4::unit = Vector4(1.f, 0.f, 0.f, 0.f);

	Vector4::Vector4()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector4::Vector4(const Vector4& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir de ses coordonn�es cart�siennes

	Vector4::Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4::Vector4(const Vector2& vector, float z, float w)
	{
		x = vector.x;
		y = vector.y;
		this->z = z;
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector2& vector, float w)
	{
		this->x = x;
		y = vector.x;
		z = vector.y;
		this->w = w;
	}

	Vector4::Vector4(float x, float y, const Vector2& vector)
	{
		this->x = x;
		this->y = y;
		z = vector.x;
		w = vector.y;
	}

	Vector4::Vector4(const Vector3& vector, float w)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector3& vector)
	{
		this->x = x;
		y = vector.x;
		z = vector.y;
		w = vector.z;
	}

	Vector4::Vector4(const std::array<float, 4>& vector)
	{
		*this = vector;
	}

	Vector4::Vector4(const glm::vec4& vector)
	{
		*this = vector;
	}

	Vector4::Vector4(const sf::Color& color)
	{
		*this = color;
	}

	// Assignations

	Vector4& Vector4::operator=(const Vector4& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;

		return *this;
	}

	Vector4& Vector4::operator=(float number)
	{
		x = number;
		y = number;
		z = number;
		w = number;

		return *this;
	}

	Vector4& Vector4::operator=(const std::array<float, 4>& vector)
	{
		x = vector[0];
		y = vector[1];
		z = vector[2];
		w = vector[3];

		return *this;
	}

	Vector4& Vector4::operator=(const glm::vec4& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;

		return *this;
	}

	Vector4& Vector4::operator=(const sf::Color& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;
		w = color.a;

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& vector)
	{
		*this = *this + vector;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& vector)
	{
		*this = *this - vector;
		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& vector)
	{
		*this = *this * vector;
		return *this;
	}

	Vector4& Vector4::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& vector)
	{
		*this = *this / vector;
		return *this;
	}

	Vector4& Vector4::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector4 Vector4::operator+() const
	{
		return *this;
	}

	Vector4 Vector4::operator-() const
	{
		return null - *this;
	}

	float Vector4::dot(const Vector4& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	// Donne la norme du vecteur

	float Vector4::get_norm() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	// Donne la norme du vecteur au carré

	float Vector4::get_norm_2() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Vector4 Vector4::get_normalized() const
	{
		if (get_norm() != 0.f)
			return *this / get_norm();

		return unit;
	}

	const float* Vector4::get_ptr() const
	{
		return &x;
	}

	float Vector4::get_distance(const Vector4& point) const
	{
		return (point - *this).get_norm();
	}

	float Vector4::get_distance_2(const Vector4& point) const
	{
		return (point - *this).get_norm_2();
	}

	// Modifie la norme du vecteur

	void Vector4::set_norm(float norm)
	{
		*this = get_normalized() * norm;
	}

	// Normalise le vecteur

	void Vector4::normalize()
	{
		if (get_norm() != 0.f)
			*this /= get_norm();

		else
			*this = unit;
	}

	// Met toutes les composantes � z�ro

	void Vector4::clear()
	{
		*this = null;
	}

	std::array<float, 4> Vector4::to_array() const
	{
		return { x, y, z, w };
	}

	glm::vec4 Vector4::to_glm() const
	{
		return glm::vec4(x, y, z, w);
	}

	// Addition

	Vector4 operator+(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z, vector_1.w + vector_2.w);
	}

	// Soustraction

	Vector4 operator-(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z, vector_1.w - vector_2.w);
	}

	// Produits

	Vector4 operator*(float number, const Vector4& vector)
	{
		return Vector4(number * vector.x, number * vector.y, number * vector.z, number * vector.w);
	}

	Vector4 operator*(const Vector4& vector, float number)
	{
		return Vector4(vector.x * number, vector.y * number, vector.z * number, vector.w + number);
	}

	Vector4 operator*(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z, vector_1.w * vector_2.w);
	}

	// Division

	Vector4 operator/(float number, const Vector4& vector)
	{
		return Vector4((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f), (vector.z != 0.f ? number / vector.z : 0.f), (vector.w != 0.f ? number / vector.w : 0.f));
	}

	Vector4 operator/(const Vector4& vector, float number)
	{
		if (number == 0.f)
			return Vector4::null;

		return Vector4(vector.x / number, vector.y / number, vector.z / number, vector.w / number);
	}

	Vector4 operator/(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f), (vector_2.z != 0.f ? vector_1.z / vector_2.z : 0.f), (vector_2.w != 0.f ? vector_1.w / vector_2.w : 0.f));
	}

	float dot(const Vector4& vector_1, const Vector4& vector_2)
	{
		return vector_1.dot(vector_2);
	}

	// Egalit�s

	bool operator==(const Vector4& vector_1, const Vector4& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z && vector_1.w == vector_2.w);
	}

	bool operator!=(const Vector4& vector_1, const Vector4& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	// Affichage

	std::ostream& operator<<(std::ostream& os, const Vector4& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return os;
	}

	float distance(const Vector4& point_1, const Vector4& point_2)
	{
		return point_1.get_distance(point_2);
	}

	float distance_2(const Vector4& point_1, const Vector4& point_2)
	{
		return point_1.get_distance_2(point_2);
	}

	Vector4 normalized(const Vector4& vector)
	{
		return vector.get_normalized();
	}

	std::array<float, 4> to_array(const Vector4& vector)
	{
		return vector.to_array();
	}

	glm::vec4 to_glm(const Vector4& vector)
	{
		return vector.to_glm();
	}
}
