#include "dim/dimension3D.h"

namespace dim
{
	const Mesh	Mesh::screen		= Mesh::Screen();
	const Mesh	Mesh::circle_64		= Mesh::Circle(64);
	const Mesh	Mesh::cone_64		= Mesh::Cone(64);
	const Mesh	Mesh::cube			= Mesh::Cube();
	const Mesh	Mesh::cylinder_64	= Mesh::Cylinder(64);
	const Mesh	Mesh::null			= Mesh();
	const Mesh	Mesh::sphere_64		= Mesh::Sphere(64, 64);
	const Mesh	Mesh::square		= Mesh::Square();

	Mesh::Vertex::Vertex()
	{
		name.clear();
		vertices.clear();
		nb_dimensions = 0;
	}

	Mesh::Vertex::Vertex(const Vertex& other)
	{
		*this = other;
	}

	Mesh::Vertex::Vertex(const std::string& name, const std::vector<float>& vertices, uint16_t nb_dimensions)
	{
		this->name = name;
		this->vertices = vertices;
		this->nb_dimensions = nb_dimensions;
	}

	Mesh::Vertex::Vertex(const std::string& name, const std::vector<Vector2>& vertices)
	{
		this->name = name;
		nb_dimensions = 2;

		for (auto& vertex : vertices)
		{
			this->vertices.push_back(vertex.x);
			this->vertices.push_back(vertex.y);
		}
	}

	Mesh::Vertex::Vertex(const std::string& name, const std::vector<Vector3>& vertices)
	{
		this->name = name;
		nb_dimensions = 3;

		for (auto& vertex : vertices)
		{
			this->vertices.push_back(vertex.x);
			this->vertices.push_back(vertex.y);
			this->vertices.push_back(vertex.z);
		}
	}

	Mesh::Vertex::Vertex(const std::string& name, const std::vector<Vector4>& vertices)
	{
		this->name = name;
		nb_dimensions = 4;

		for (auto& vertex : vertices)
		{
			this->vertices.push_back(vertex.x);
			this->vertices.push_back(vertex.y);
			this->vertices.push_back(vertex.z);
			this->vertices.push_back(vertex.w);
		}
	}

	Mesh::Vertex& Mesh::Vertex::operator=(const Vertex& other)
	{
		name = other.name;
		vertices = other.vertices;
		nb_dimensions = other.nb_dimensions;

		return *this;
	}

	Mesh Mesh::Screen()
	{
		std::vector<float> positions;
		std::vector<float> uvs;

		positions =
		{
			-1.f, -1.f,  0.f,
			 1.f,  1.f,  0.f,
			 1.f, -1.f,  0.f,
			-1.f, -1.f,  0.f,
			-1.f,  1.f,  0.f,
			 1.f,  1.f,  0.f
		};

		uvs =
		{
			0.f, 0.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f
		};

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh::Mesh()
	{
		vertex_array.clear();
	}

	Mesh::Mesh(const Mesh& other)
	{
		*this = other;
	}

	Mesh& Mesh::operator=(const Mesh& other)
	{
		vertex_array = other.vertex_array;

		return *this;
	}

	void Mesh::set_vertices(const std::string& name, const std::vector<float>& vertices, uint16_t nb_dimensions)
	{
		auto vertex = std::find_if(vertex_array.begin(), vertex_array.end(), [&](Vertex& i) -> bool { return i.name == name; });

		if (vertex == vertex_array.end())
			vertex_array.emplace_back(name, vertices, nb_dimensions);

		else
		{
			vertex->name = name;
			vertex->vertices = vertices;
			vertex->nb_dimensions = nb_dimensions;
		}
	}

	void Mesh::set_vertices(const std::string& name, const std::vector<Vector2>& vertices)
	{
		auto vertex = std::find_if(vertex_array.begin(), vertex_array.end(), [&](Vertex& i) -> bool { return i.name == name; });

		if (vertex == vertex_array.end())
			vertex_array.emplace_back(name, vertices);

		else
		{
			vertex->name = name;
			vertex->vertices.clear();
			vertex->nb_dimensions = 2;

			for (auto& v : vertices)
			{
				vertex->vertices.push_back(v.x);
				vertex->vertices.push_back(v.y);
			}
		}
	}

	void Mesh::set_vertices(const std::string& name, const std::vector<Vector3>& vertices)
	{
		auto vertex = std::find_if(vertex_array.begin(), vertex_array.end(), [&](Vertex& i) -> bool { return i.name == name; });

		if (vertex == vertex_array.end())
			vertex_array.emplace_back(name, vertices);

		else
		{
			vertex->name = name;
			vertex->vertices.clear();
			vertex->nb_dimensions = 3;

			for (auto& v : vertices)
			{
				vertex->vertices.push_back(v.x);
				vertex->vertices.push_back(v.y);
				vertex->vertices.push_back(v.z);
			}
		}
	}

	void Mesh::set_vertices(const std::string& name, const std::vector<Vector4>& vertices)
	{
		auto vertex = std::find_if(vertex_array.begin(), vertex_array.end(), [&](Vertex& i) -> bool { return i.name == name; });

		if (vertex == vertex_array.end())
			vertex_array.emplace_back(name, vertices);

		else
		{
			vertex->name = name;
			vertex->vertices.clear();
			vertex->nb_dimensions = 4;

			for (auto& v : vertices)
			{
				vertex->vertices.push_back(v.x);
				vertex->vertices.push_back(v.y);
				vertex->vertices.push_back(v.z);
				vertex->vertices.push_back(v.w);
			}
		}
	}

	void Mesh::set_positions(const std::vector<float>& positions)
	{
		set_vertices("positions", positions, 3);
	}

	void Mesh::set_positions(const std::vector<Vector3>& positions)
	{
		set_vertices("positions", positions);
	}

	void Mesh::set_normals(const std::vector<float>& normals)
	{
		set_vertices("normals", normals, 3);
	}

	void Mesh::set_normals(const std::vector<Vector3>& normals)
	{
		set_vertices("normals", normals);
	}

	void Mesh::set_uvs(const std::vector<float>& uvs)
	{
		set_vertices("uvs", uvs, 2);
	}

	void Mesh::set_uvs(const std::vector<Vector2>& uvs)
	{
		set_vertices("uvs", uvs);
	}

	uint32_t Mesh::get_data_size() const
	{
		uint32_t data_size = 0;

		for (auto& vertex : vertex_array)
			data_size += vertex.vertices.size();

		return data_size;
	}

	uint32_t Mesh::get_nb_vertices() const
	{
		if (vertex_array.size() == 0)
			return 0;

		return (float)vertex_array.front().vertices.size() / (float)vertex_array.front().nb_dimensions;
	}

	Mesh Mesh::Circle(uint32_t nb_edges)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		positions.resize(9 * nb_edges, 0.f);
		normals.resize(9 * nb_edges, 0.f);
		uvs.resize(6 * nb_edges, 0.f);

		for (uint32_t i = 0; i < nb_edges; i++)
		{
			float pos[] =
			{
				(float)cos(i * 2.f * PI / nb_edges), (float)sin(i * 2.f * PI / nb_edges), 0.f,
				0.f, 0.f, 0.f,
				(float)cos((i + 1) * 2.f * PI / nb_edges), (float)sin((i + 1) * 2.f * PI / nb_edges), 0.f
			};

			for (uint32_t j = 0; j < 9; j++)
				positions[9 * i + j] = 0.5f * pos[j];

			for (uint32_t j = 0; j < 3; j++)
				for (uint32_t k = 0; k < 2; k++)
					uvs[6 * i + 2 * j + k] = positions[9 * i + 3 * j + k] + 0.5f;

			for (uint32_t j = 0; j < 3; j++)
			{
				float normal[] = { 0.f, 0.f, 1.f };

				for (uint32_t k = 0; k < 3; k++)
					normals[9 * i + 3 * j + k] = normal[k];
			}
		}

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh Mesh::Cone(uint32_t nb_lattitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		float radius = 0.5f;
		positions.resize(3 * 6 * nb_lattitudes, 0.f);
		normals.resize(3 * 6 * nb_lattitudes, 0.f);
		uvs.resize(2 * 6 * nb_lattitudes, 0.f);

		for (uint32_t i = 0; i < nb_lattitudes; i++)
		{
			double pos[] =
			{
				radius * cos(i * 2.f * PI / nb_lattitudes), radius * sin(i * 2.f * PI / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * PI / nb_lattitudes), radius * sin((i + 1) * 2.f * PI / nb_lattitudes), -1.f / 2.f,
				cos((i + 1) * 2.f * PI / nb_lattitudes), sin((i + 1) * 2.f * PI / nb_lattitudes), 1.f / 2.f,

				radius * cos(i * 2.f * PI / nb_lattitudes), radius * sin(i * 2.f * PI / nb_lattitudes), -1.f / 2.f,
				cos((i + 1) * 2.f * PI / nb_lattitudes), sin((i + 1) * 2 * PI / nb_lattitudes), 1.f / 2.f,
				cos(i * 2.f * PI / nb_lattitudes), sin(i * 2.f * PI / nb_lattitudes), 1.f / 2.f
			};

			double uvPos[] =
			{
				i / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 1.f,

				i / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 1.f,
				i / (double)nb_lattitudes, 1.f
			};

			for (uint32_t j = 0; j < 18; j++)
				positions[18 * i + j] = pos[j];

			for (uint32_t j = 0; j < 12; j++)
				uvs[12 * i + j] = uvPos[j];

			float angle = PI / 4.f;
			glm::vec3 normalI = glm::rotate(glm::mat4(1.f), (float)(i * 2.f * PI / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);
			glm::vec3 normalI2 = glm::rotate(glm::mat4(1.f), (float)((i + 1.f) * 2.f * PI / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);

			for (uint32_t j = 0; j < 3; j++)
			{
				normals[18 * i + 0 + j] = normalI[j];
				normals[18 * i + 3 + j] = normalI2[j];
				normals[18 * i + 6 + j] = normalI2[j];
				normals[18 * i + 9 + j] = normalI[j];
				normals[18 * i + 12 + j] = normalI2[j];
				normals[18 * i + 15 + j] = normalI[j];
			}
		}

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh Mesh::Cube()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		positions =
		{
			//Back
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,

			//Front
			-0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			 //Left
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,

			//Right
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,

			//Top
			0.5f,  0.5f, -0.5f,
		   -0.5f,  0.5f, -0.5f,
		   -0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
		   -0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			//Bottom
		   0.5f, -0.5f, -0.5f,
		  -0.5f, -0.5f,  0.5f,
		  -0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f,  0.5f,
		  -0.5f, -0.5f,  0.5f
		};

		normals =
		{
			//Back
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,

			//Front
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,

			//Left
			-1.f, 0.f, 0.f,
			-1.f, 0.f, 0.f,
			-1.f, 0.f, 0.f,
			-1.f, 0.f, 0.f,
			-1.f, 0.f, 0.f,
			-1.f, 0.f, 0.f,

			//Right
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,

			//Top
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,

			//Bottom
			0.f, -1.f, 0.f,
			0.f, -1.f, 0.f,
			0.f, -1.f, 0.f,
			0.f, -1.f, 0.f,
			0.f, -1.f, 0.f,
			0.f, -1.f, 0.f
		};

		uvs =
		{
			//Back
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,

			//Front
			0.f, 1.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,

			//Left
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,

			//Right
			0.f, 1.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,

			//Top
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			//Bottom
			0.f, 0.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f
		};

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh Mesh::Cylinder(uint32_t nb_lattitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		float radius = 0.5f;

		positions.resize(3 * 6 * nb_lattitudes, 0.f);
		normals.resize(3 * 6 * nb_lattitudes, 0.f);
		uvs.resize(2 * 6 * nb_lattitudes, 0.f);

		for (uint32_t i = 0; i < nb_lattitudes; i++)
		{
			double pos[] =
			{
				radius * cos(i * 2.f * PI / nb_lattitudes), radius * sin(i * 2.f * PI / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * PI / nb_lattitudes), radius * sin((i + 1) * 2 * PI / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * PI / nb_lattitudes), radius * sin((i + 1) * 2 * PI / nb_lattitudes), 1.f / 2.f,

				radius * cos(i * 2.f * PI / nb_lattitudes), radius * sin(i * 2.f * PI / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * PI / nb_lattitudes), radius * sin((i + 1) * 2.f * PI / nb_lattitudes), 1.f / 2.f,
				radius * cos(i * 2.f * PI / nb_lattitudes), radius * sin(i * 2.f * PI / nb_lattitudes), 1.f / 2.f
			};

			double uvPos[] =
			{
				i / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 1.f,

				i / (double)nb_lattitudes, 0.f,
				(i + 1) / (double)nb_lattitudes, 1.f,
				i / (double)nb_lattitudes, 1.f
			};

			for (uint32_t j = 0; j < 18; j++)
				positions[18 * i + j] = pos[j];

			for (uint32_t j = 0; j < 12; j++)
				uvs[12 * i + j] = uvPos[j];

			for (uint32_t j = 0; j < 6; j++)
			{
				for (uint32_t k = 0; k < 2; k++)
					normals[18 * i + 3 * j + k] = pos[3 * j + k];

				normals[18 * i + 3 * j + 2] = 0.f;
			}
		}

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh Mesh::Sphere(uint32_t nb_latitudes, uint32_t nb_longitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		float radius = 0.5f;

		// Determine position
		glm::vec3* vertexCoord = (glm::vec3*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec3));
		glm::vec2* uvCoord = (glm::vec2*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec2));

		for (unsigned int i = 0; i < nb_longitudes; i++)
		{
			double theta = 2.f * PI / (nb_longitudes - 1) * i;

			for (unsigned int j = 0; j < nb_latitudes; j++)
			{
				double phi = PI / (nb_latitudes - 1) * j;
				double pos[] = { sin(phi) * sin(theta), cos(phi), cos(theta) * sin(phi) };
				double uvs[] = { i / (double)(nb_longitudes), j / (double)(nb_latitudes) };

				for (unsigned int k = 0; k < 3; k++)
					vertexCoord[i * nb_latitudes + j][k] = radius * pos[k];

				for (unsigned int k = 0; k < 2; k++)
					uvCoord[i * nb_latitudes + j][k] = uvs[k];
			}
		}

		// Determine draw orders
		unsigned int* order = (unsigned int*)malloc(nb_longitudes * (nb_latitudes - 1) * sizeof(unsigned int) * 6);

		for (unsigned int i = 0; i < nb_longitudes; i++)
		{
			for (unsigned int j = 0; j < nb_latitudes - 1; j++)
			{
				unsigned int o[] =
				{
					i * nb_latitudes + j, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + (j + 1) % nb_latitudes, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + j,
					i * nb_latitudes + j, i * (nb_latitudes)+(j + 1) % nb_latitudes, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + (j + 1) % nb_latitudes
				};

				for (unsigned int k = 0; k < 6; k++)
					order[(nb_latitudes - 1) * i * 6 + j * 6 + k] = o[k];
			}
		}

		// Merge everything
		positions.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.);
		normals.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.);
		uvs.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 2, 0.);

		for (uint32_t i = 0; i < nb_latitudes * (nb_longitudes - 1) * 6; i++)
		{
			uint32_t indice = order[i];

			for (uint32_t j = 0; j < 3; j++)
			{
				positions[3 * i + j] = vertexCoord[indice][j];
				normals[3 * i + j] = glm::normalize(vertexCoord[indice])[j];
			}

			for (uint32_t j = 0; j < 2; j++)
				uvs[2 * i + j] = uvCoord[indice][j];
		}

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}

	Mesh Mesh::Square()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> uvs;

		positions =
		{
			-0.5f, -0.5f,  0.f,
			 0.5f,  0.5f,  0.f,
			 0.5f, -0.5f,  0.f,
			-0.5f, -0.5f,  0.f,
			-0.5f,  0.5f,  0.f,
			 0.5f,  0.5f,  0.f
		};

		normals =
		{
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f
		};

		uvs =
		{
			0.f, 1.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 0.f
		};

		Mesh mesh;
		mesh.set_positions(positions);
		mesh.set_normals(normals);
		mesh.set_uvs(uvs);
		return mesh;
	}
}
