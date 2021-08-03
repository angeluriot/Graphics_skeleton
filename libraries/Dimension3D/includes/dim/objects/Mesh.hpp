#ifndef MESH_H
#define MESH_H

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/opengl/Shader.hpp"

namespace dim
{
	class VertexBuffer;

	class Mesh
	{
	public:

		std::vector<Vector3>	positions;
		std::vector<Vector3>	normals;
		std::vector<Vector2>	texcoords;

		static const Mesh	circle_64;
		static const Mesh	cone_64;
		static const Mesh	cube;
		static const Mesh	empty_cube;
		static const Mesh	cylinder_64;
		static const Mesh	null;
		static const Mesh	sphere_64;
		static const Mesh	square;
		static const Mesh	screen;

							Mesh();
							Mesh(const Mesh& other) = default;

		Mesh&				operator=(const Mesh& other) = default;
		Mesh&				operator+=(const Mesh& other);
		Mesh				operator+(const Mesh& other);

		unsigned int		get_data_size() const;
		unsigned int		get_positions_size() const;
		unsigned int		get_normals_size() const;
		unsigned int		get_texcoords_size() const;
		unsigned int		get_nb_vertices() const;

		void				clear();

		static Mesh			Circle(unsigned int nb_edges);
		static Mesh			Cone(unsigned int nb_lattitudes);
		static Mesh			Cube();
		static Mesh			EmptyCube();
		static Mesh			Cylinder(unsigned int nb_lattitudes);
		static Mesh			Sphere(unsigned int nb_latitudes, unsigned int nb_longitudes);
		static Mesh			Square();
		static Mesh			Screen();
	};

	Mesh					operator*(const glm::mat4& matrix, const Mesh& mesh);
}

#endif
