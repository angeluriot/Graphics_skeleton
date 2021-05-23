#include "dim/dimension3D.h"

// Construit un vecteur
namespace dim
{
	const Vector3 Vector3::null = Vector3();
	const Vector3 Vector3::unit = Vector3(1.f, 0.f, 0.f);

	Vector3::Vector3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector3::Vector3(const Vector3& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir de ses coordonn�es cart�siennes

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3::Vector3(const Vector4& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
	}

	Vector3::Vector3(const Vector2& vector, float z)
	{
		x = vector.x;
		y = vector.y;
		this->z = z;
	}

	Vector3::Vector3(float x, const Vector2& vector)
	{
		this->x = x;
		y = vector.x;
		z = vector.y;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector3::Vector3(const std::array<float, 3>& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector3::Vector3(const glm::vec3& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector3::Vector3(const sf::Vector3f& vector)
	{
		*this = vector;
	}

	// Construit un vecteur � partir d'un autre vecteur

	Vector3::Vector3(const sf::Vector3i& vector)
	{
		*this = vector;
	}

	Vector3::Vector3(const sf::Color& color)
	{
		*this = color;
	}

	Vector3 Vector3::Cartesian(float x, float y, float z)
	{
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Spherical(float norm, float theta, float phi)
	{
		return Vector3(norm * sin(theta) * sin(phi), norm * cos(phi), norm * cos(theta) * sin(phi));
	}

	// Assignations

	Vector3& Vector3::operator=(const Vector3& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;

		return *this;
	}

	Vector3& Vector3::operator=(float number)
	{
		x = number;
		y = number;
		z = number;

		return *this;
	}

	Vector3& Vector3::operator=(const std::array<float, 3>& vector)
	{
		x = vector[0];
		y = vector[1];
		z = vector[2];

		return *this;
	}

	Vector3& Vector3::operator=(const glm::vec3& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Vector3f& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Vector3i& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Color& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& vector)
	{
		*this = *this + vector;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& vector)
	{
		*this = *this - vector;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& vector)
	{
		*this = *this * vector;
		return *this;
	}

	Vector3& Vector3::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& vector)
	{
		*this = *this / vector;
		return *this;
	}

	Vector3& Vector3::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector3& Vector3::operator^=(const Vector3& vector)
	{
		*this = *this ^ vector;
		return *this;
	}

	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return null - *this;
	}

	float Vector3::dot(const Vector3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	// Donne la norme du vecteur

	float Vector3::get_norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	// Donne la norme du vecteur au carr�

	float Vector3::get_norm_2() const
	{
		return x * x + y * y + z * z;
	}

	// Donne l'angle theta du vecteur

	float Vector3::get_theta() const
	{
		return Vector2(z, x).get_angle();
	}

	// Donne l'angle phi du vecteur

	float Vector3::get_phi() const
	{
		if (get_norm() == 0.f)
			return 0.f;

		return acos(y / get_norm());
	}

	Vector3 Vector3::get_normalized() const
	{
		if (get_norm() != 0.f)
			return *this / get_norm();

		return unit;
	}

	const float* Vector3::get_ptr() const
	{
		return &x;
	}

	float Vector3::get_distance(const Vector3& point) const
	{
		return (point - *this).get_norm();
	}

	float Vector3::get_distance_2(const Vector3& point) const
	{
		return (point - *this).get_norm_2();
	}

	float Vector3::get_theta(const Vector3& point) const
	{
		return (point - *this).get_theta();
	}

	float Vector3::get_phi(const Vector3& point) const
	{
		return (point - *this).get_phi();
	}

	// Modifie la norme du vecteur

	void Vector3::set_norm(float norm)
	{
		*this = get_normalized() * norm;
	}

	// Modifie l'angle theta du vecteur

	void Vector3::set_theta(float theta)
	{
		*this = Spherical(get_norm(), theta, get_phi());
	}

	// Modifie l'angle phi du vecteur

	void Vector3::set_phi(float phi)
	{
		*this = Spherical(get_norm(), get_theta(), phi);
	}

	// Normalise le vecteur

	void Vector3::normalize()
	{
		if (get_norm() != 0.f)
			*this /= get_norm();

		else
			*this = unit;
	}

	// Met toutes les composantes � z�ro

	void Vector3::clear()
	{
		*this = null;
	}

	std::array<float, 3> Vector3::to_array() const
	{
		return { x, y, z };
	}

	glm::vec3 Vector3::to_glm() const
	{
		return glm::vec3(x, y, z);
	}

	sf::Vector3f Vector3::to_sf_float() const
	{
		return sf::Vector3f(x, y, z);
	}

	sf::Vector3i Vector3::to_sf_int() const
	{
		return sf::Vector3i(x, y, z);
	}

	// Addition

	Vector3 operator+(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z);
	}

	// Soustraction

	Vector3 operator-(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z);
	}

	// Produits

	Vector3 operator*(float number, const Vector3& vector)
	{
		return Vector3(number * vector.x, number * vector.y, number * vector.z);
	}

	Vector3 operator*(const Vector3& vector, float number)
	{
		return Vector3(vector.x * number, vector.y * number, vector.z * number);
	}

	Vector3 operator*(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z);
	}

	// Division

	Vector3 operator/(float number, const Vector3& vector)
	{
		return Vector3((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f), (vector.z != 0.f ? number / vector.z : 0.f));
	}

	Vector3 operator/(const Vector3& vector, float number)
	{
		if (number == 0.f)
			return Vector3::null;

		return Vector3(vector.x / number, vector.y / number, vector.z / number);
	}

	Vector3 operator/(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f), (vector_2.z != 0.f ? vector_1.z / vector_2.z : 0.f));
	}

	// Produit vectoriel

	Vector3 operator^(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.y * vector_2.z - vector_1.z * vector_2.y, vector_1.z * vector_2.x - vector_1.x * vector_2.z, vector_1.x * vector_2.y - vector_1.y * vector_2.x);
	}

	float dot(const Vector3& vector_1, const Vector3& vector_2)
	{
		return vector_1.dot(vector_2);
	}

	// Egalit�s

	bool operator==(const Vector3& vector_1, const Vector3& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z);
	}

	bool operator!=(const Vector3& vector_1, const Vector3& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	// Affichage

	std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return os;
	}

	float distance(const Vector3& point_1, const Vector3& point_2)
	{
		return point_1.get_distance(point_2);
	}

	float distance_2(const Vector3& point_1, const Vector3& point_2)
	{
		return point_1.get_distance_2(point_2);
	}

	float theta(const Vector3& point_1, const Vector3& point_2)
	{
		return point_1.get_theta(point_2);
	}

	float phi(const Vector3& point_1, const Vector3& point_2)
	{
		return point_1.get_phi(point_2);
	}

	Vector3 normalized(const Vector3& vector)
	{
		return vector.get_normalized();
	}

	std::array<float, 3> to_array(const Vector3& vector)
	{
		return vector.to_array();
	}

	glm::vec3 to_glm(const Vector3& vector)
	{
		return vector.to_glm();
	}

	sf::Vector3f to_sf_float(const Vector3& vector)
	{
		return vector.to_sf_float();
	}

	sf::Vector3i to_sf_int(const Vector3& vector)
	{
		return vector.to_sf_int();
	}
}
