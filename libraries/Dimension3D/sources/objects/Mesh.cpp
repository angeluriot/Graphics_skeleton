#include "dim/dimension3D.hpp"

namespace dim
{
	const Mesh	Mesh::circle_64		= Mesh::Circle(64);
	const Mesh	Mesh::cone_64		= Mesh::Cone(64);
	const Mesh	Mesh::cube			= Mesh::Cube();
	const Mesh	Mesh::empty_cube	= Mesh::EmptyCube();
	const Mesh	Mesh::cylinder_64	= Mesh::Cylinder(64);
	const Mesh	Mesh::null			= Mesh();
	const Mesh	Mesh::sphere_64		= Mesh::Sphere(64, 64);
	const Mesh	Mesh::square		= Mesh::Square();
	const Mesh	Mesh::screen		= Mesh::Screen();

	Mesh::Mesh()
	{
		positions.clear();
		normals.clear();
		texcoords.clear();
	}

	Mesh& Mesh::operator+=(const Mesh& other)
	{
		for (auto& position : other.positions)
			positions.push_back(position);

		for (auto& normal : other.normals)
			normals.push_back(normal);

		for (auto& texcoord : other.texcoords)
			texcoords.push_back(texcoord);

		return *this;
	}

	Mesh Mesh::operator+(const Mesh& other)
	{
		Mesh mesh;

		for (auto& position : positions)
			mesh.positions.push_back(position);

		for (auto& normal : normals)
			mesh.normals.push_back(normal);

		for (auto& texcoord : texcoords)
			mesh.texcoords.push_back(texcoord);

		for (auto& position : other.positions)
			mesh.positions.push_back(position);

		for (auto& normal : other.normals)
			mesh.normals.push_back(normal);

		for (auto& texcoord : other.texcoords)
			mesh.texcoords.push_back(texcoord);

		return mesh;
	}

	unsigned int Mesh::get_data_size() const
	{
		return static_cast<unsigned int>(positions.size() * sizeof(Vector3) + normals.size() * sizeof(Vector3) + texcoords.size() * sizeof(Vector2));
	}

	unsigned int Mesh::get_positions_size() const
	{
		return static_cast<unsigned int>(positions.size() * sizeof(Vector3));
	}

	unsigned int Mesh::get_normals_size() const
	{
		return static_cast<unsigned int>(normals.size() * sizeof(Vector3));
	}

	unsigned int Mesh::get_texcoords_size() const
	{
		return static_cast<unsigned int>(texcoords.size() * sizeof(Vector2));
	}

	unsigned int Mesh::get_nb_vertices() const
	{
		return static_cast<unsigned int>(positions.size());
	}

	void Mesh::clear()
	{
		positions.clear();
		normals.clear();
		texcoords.clear();
	}

	Mesh Mesh::Circle(unsigned int nb_edges)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		positions.resize(9 * nb_edges, 0.f);
		normals.resize(9 * nb_edges, 0.f);
		texcoords.resize(6 * nb_edges, 0.f);

		for (uint16_t i = 0; i < nb_edges; i++)
		{
			float pos[] =
			{
				(float)cos(i * 2.f * pi / nb_edges), (float)sin(i * 2.f * pi / nb_edges), 0.f,
				0.f, 0.f, 0.f,
				(float)cos((i + 1) * 2.f * pi / nb_edges), (float)sin((i + 1) * 2.f * pi / nb_edges), 0.f
			};

			for (uint16_t j = 0; j < 9; j++)
				positions[9 * i + j] = 0.5f * pos[j];

			for (uint16_t j = 0; j < 3; j++)
				for (uint16_t k = 0; k < 2; k++)
					texcoords[6 * i + 2 * j + k] = positions[9 * i + 3 * j + k] + 0.5f;

			for (uint16_t j = 0; j < 3; j++)
			{
				float normal[] = { 0.f, 0.f, 1.f };

				for (uint16_t k = 0; k < 3; k++)
					normals[9 * i + 3 * j + k] = normal[k];
			}
		}

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Cone(unsigned int nb_lattitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		float radius = 0.5f;
		positions.resize(3 * 6 * nb_lattitudes, 0.f);
		normals.resize(3 * 6 * nb_lattitudes, 0.f);
		texcoords.resize(2 * 6 * nb_lattitudes, 0.f);

		for (uint16_t i = 0; i < nb_lattitudes; i++)
		{
			float pos[] =
			{
				radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), -1.f / 2.f,
				cos((i + 1) * 2.f * pi / nb_lattitudes), sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,

				radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
				cos((i + 1) * 2.f * pi / nb_lattitudes), sin((i + 1) * 2 * pi / nb_lattitudes), 1.f / 2.f,
				cos(i * 2.f * pi / nb_lattitudes), sin(i * 2.f * pi / nb_lattitudes), 1.f / 2.f
			};

			float uvPos[] =
			{
				i / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 1.f,

				i / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 1.f,
				i / (float)nb_lattitudes, 1.f
			};

			for (int j = 0; j < 18; j++)
				positions[18 * i + j] = pos[j];

			for (int j = 0; j < 12; j++)
				texcoords[12 * i + j] = uvPos[j];

			float angle = pi / 4.f;
			glm::vec3 normalI = glm::rotate(glm::mat4(1.f), (float)(i * 2.f * pi / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);
			glm::vec3 normalI2 = glm::rotate(glm::mat4(1.f), (float)((i + 1.f) * 2.f * pi / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);

			for (int j = 0; j < 3; j++)
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

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Cube()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		positions =
		{
			//Back
			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			//Front
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			//Left
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,

			//Right
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,

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

		texcoords =
		{
			//Back
			1.f, 0.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			//Front
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 1.f,

			//Left
			1.f, 0.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			//Right
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 1.f,

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

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::EmptyCube()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		positions =
		{
			//Back
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,

			//Front
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			//Top
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,

			//Bottom
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f, -0.5f
		};

		normals =
		{
			//Back
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,

			//Front
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,

			//Top
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,

			//Bottom
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 0.f, 0.f
		};

		texcoords =
		{
			//Back
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,

			//Front
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,

			//Top
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,

			//Bottom
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f,
			0.f, 0.f
		};

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Cylinder(unsigned int nb_lattitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		float radius = 0.5f;

		positions.resize(3 * 6 * nb_lattitudes, 0.f);
		normals.resize(3 * 6 * nb_lattitudes, 0.f);
		texcoords.resize(2 * 6 * nb_lattitudes, 0.f);

		for (uint16_t i = 0; i < nb_lattitudes; i++)
		{
			float pos[] =
			{
				radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2 * pi / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2 * pi / nb_lattitudes), 1.f / 2.f,

				radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
				radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,
				radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), 1.f / 2.f
			};

			float uvPos[] =
			{
				i / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 1.f,

				i / (float)nb_lattitudes, 0.f,
				(i + 1) / (float)nb_lattitudes, 1.f,
				i / (float)nb_lattitudes, 1.f
			};

			for (int j = 0; j < 18; j++)
				positions[18 * i + j] = pos[j];

			for (int j = 0; j < 12; j++)
				texcoords[12 * i + j] = uvPos[j];

			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 2; k++)
					normals[18 * i + 3 * j + k] = pos[3 * j + k];

				normals[18 * i + 3 * j + 2] = 0.f;
			}
		}

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Sphere(unsigned int nb_latitudes, unsigned int nb_longitudes)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		float radius = 0.5f;

		// Determine position
		glm::vec3* vertexCoord = (glm::vec3*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec3));
		glm::vec2* uvCoord = (glm::vec2*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec2));

		for (int i = 0; i < (int)nb_longitudes; i++)
		{
			float theta = 2.f * pi / (nb_longitudes - 1) * i;

			for (int j = 0; j < (int)nb_latitudes; j++)
			{
				float phi = pi / (nb_latitudes - 1) * j;
				float pos[] = { sin(phi) * sin(theta), cos(phi), cos(theta) * sin(phi) };
				float uvs[] = { i / (float)(nb_longitudes), j / (float)(nb_latitudes) };

				for (int k = 0; k < 3; k++)
					vertexCoord[i * nb_latitudes + j][k] = radius * pos[k];

				for (int k = 0; k < 2; k++)
					uvCoord[i * nb_latitudes + j][k] = uvs[k];
			}
		}

		// Determine draw orders
		int* order = (int*)malloc(nb_longitudes * (nb_latitudes - 1) * sizeof(int) * 6);

		for (int i = 0; i < (int)nb_longitudes; i++)
		{
			for (int j = 0; j < (int)nb_latitudes - 1; j++)
			{
				int o[] =
				{
					i * (int)nb_latitudes + j, (i + 1) * ((int)nb_latitudes) % ((int)nb_latitudes * (int)nb_longitudes) + (j + 1) % (int)nb_latitudes, (i + 1) * ((int)nb_latitudes) % ((int)nb_latitudes * (int)nb_longitudes) + j,
					i * (int)nb_latitudes + j, i * ((int)nb_latitudes)+(j + 1) % (int)nb_latitudes, (i + 1) * ((int)nb_latitudes) % ((int)nb_latitudes * (int)nb_longitudes) + (j + 1) % (int)nb_latitudes
				};

				for (int k = 0; k < 6; k++)
					order[(nb_latitudes - 1) * i * 6 + j * 6 + k] = o[k];
			}
		}

		// Merge everything
		positions.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.f);
		normals.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.f);
		texcoords.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 2, 0.f);

		for (int i = 0; i < (int)nb_latitudes * ((int)nb_longitudes - 1) * 6; i++)
		{
			int indice = order[i];

			for (int j = 0; j < 3; j++)
			{
				positions[3 * i + j] = vertexCoord[indice][j];
				normals[3 * i + j] = glm::normalize(vertexCoord[indice])[j];
			}

			for (int j = 0; j < 2; j++)
				texcoords[2 * i + j] = uvCoord[indice][j];
		}

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Square()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		positions =
		{
			0.5f,  0.5f,  0.f,
			-0.5f,  0.5f,  0.f,
			-0.5f, -0.5f,  0.f,
			0.5f, -0.5f,  0.f,
			0.5f,  0.5f,  0.f,
			-0.5f, -0.5f,  0.f
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

		texcoords =
		{
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 1.f
		};

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh Mesh::Screen()
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;

		positions =
		{
			1.f,  1.f,  0.f,
			-1.f,  1.f,  0.f,
			-1.f, -1.f,  0.f,
			1.f, -1.f,  0.f,
			1.f,  1.f,  0.f,
			-1.f, -1.f,  0.f
		};

		normals =
		{
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f,
			0.f, 0.f, -1.f
		};

		texcoords =
		{
			1.f, 1.f,
			0.f, 1.f,
			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 0.f
		};

		Mesh mesh;

		for (int i = 0; i < positions.size(); i += 3)
		{
			mesh.positions.push_back(Vector3(positions[i], positions[i + 1], positions[i + 2]));
			mesh.normals.push_back(Vector3(normals[i], normals[i + 1], normals[i + 2]));
		}

		for (int i = 0; i < texcoords.size(); i += 2)
			mesh.texcoords.push_back(Vector2(texcoords[i], texcoords[i + 1]));

		return mesh;
	}

	Mesh operator*(const glm::mat4& matrix, const Mesh& mesh)
	{
		Mesh result;

		for (auto& position : mesh.positions)
			result.positions.push_back(Vector3(matrix * position));

		glm::mat3 normals_matrix = glm::transpose(glm::inverse(glm::mat3(matrix)));

		for (auto& normal : mesh.normals)
			result.normals.push_back(normalized(Vector3(normals_matrix * normal)));

		result.texcoords = mesh.texcoords;

		return result;
	}
}
