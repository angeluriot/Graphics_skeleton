#ifndef MESH_H
#define MESH_H

#include "dim/utils/libraries.h"
#include "dim/vectors/Vector2.h"
#include "dim/vectors/Vector3.h"
#include "dim/vectors/Vector4.h"
#include "dim/opengl/Shader.h"

namespace dim
{
	class VertexBuffer;

	class Mesh
	{
	private:

		struct Vertex
		{
			std::string			name;
			std::vector<float>	vertices;
			uint16_t			nb_dimensions;

								Vertex();
								Vertex(const Vertex& other);
								Vertex(const std::string& name, const std::vector<float>& vertices, uint16_t nb_dimensions);
								Vertex(const std::string& name, const std::vector<Vector2>& vertices);
								Vertex(const std::string& name, const std::vector<Vector3>& vertices);
								Vertex(const std::string& name, const std::vector<Vector4>& vertices);

			Vertex&				operator=(const Vertex& other);
		};

		std::vector<Vertex>		vertex_array;

	public:

		static const Mesh	circle_64;
		static const Mesh	cone_64;
		static const Mesh	cube;
		static const Mesh	cylinder_64;
		static const Mesh	null;
		static const Mesh	sphere_64;
		static const Mesh	square;
		static const Mesh	screen;

								Mesh();
								Mesh(const Mesh& other);

		Mesh&				operator=(const Mesh& other);

		void					set_vertices(const std::string& name, const std::vector<float>& vertices, uint16_t nb_dimensions);
		void					set_vertices(const std::string& name, const std::vector<Vector2>& vertices);
		void					set_vertices(const std::string& name, const std::vector<Vector3>& vertices);
		void					set_vertices(const std::string& name, const std::vector<Vector4>& vertices);

		void					set_positions(const std::vector<float>& positions);
		void					set_positions(const std::vector<Vector3>& positions);
		void					set_normals(const std::vector<float>& normals);
		void					set_normals(const std::vector<Vector3>& normals);
		void					set_uvs(const std::vector<float>& uvs);
		void					set_uvs(const std::vector<Vector2>& uvs);

		uint32_t				get_data_size() const;
		uint32_t				get_nb_vertices() const;

		static Mesh			Circle(uint32_t nb_edges);
		static Mesh			Cone(uint32_t nb_lattitudes);
		static Mesh			Cube();
		static Mesh			Cylinder(uint32_t nb_lattitudes);
		static Mesh			Sphere(uint32_t nb_latitudes, uint32_t nb_longitudes);
		static Mesh			Square();
		static Mesh			Screen();

		friend VertexBuffer;
	};
}

#endif
