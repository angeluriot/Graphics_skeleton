#ifndef SHADER_H
#define SHADER_H

#include "dim/utils/libraries.h"
#include "dim/vectors/Vector2.h"
#include "dim/vectors/Vector3.h"
#include "dim/vectors/Vector4.h"
#include "dim/opengl/Texture.h"

namespace dim
{
	class Mesh;
	class VertexBuffer;
	void unbind_all();
	void init();

	class Shader
	{
	private:

		std::shared_ptr<sf::Shader>	ptr;
		std::string					name;
		bool						valid;

		static std::vector<Shader>	shaders;

		static void					load_default();

	public:

									Shader();
									Shader(const Shader& other);
									Shader(const std::string& name, const std::string& folder_path);
									Shader(const std::string& name, const std::string& vert_path, const std::string& frag_path);

		Shader&						operator=(const Shader& other);

		bool						load(const std::string& name, const std::string& folder_path);
		bool						load(const std::string& name, const std::string& vert_path, const std::string& frag_path);
		GLuint						get_id() const;
		bool						is_valid() const;
		void						bind() const;
		static void					unbind();

		static bool					add_shader(const Shader& shader);
		static bool					add_shader(const std::string& name, const std::string& folder_path);
		static bool					add_shader(const std::string& name, const std::string& vert_path, const std::string& frag_path);
		static Shader*				get_shader(const std::string& name);
		static GLuint				get_id(const std::string& name);

		static void					clear();

		friend						VertexBuffer;
		friend void					unbind_all();
		friend void					init();
	};
}

#endif
