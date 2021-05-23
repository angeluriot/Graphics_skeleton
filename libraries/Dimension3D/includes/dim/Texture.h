#ifndef TEXTURE_H
#define TEXTURE_H

#include "dim/libraries.h"

namespace dim
{
	class VertexBuffer;
	class FrameBuffer;
	void unbind_all();

	class Texture
	{
	public:

		enum class Warpping { Repeat = GL_REPEAT, MirroredRepeat = GL_MIRRORED_REPEAT, ClampToEdge = GL_CLAMP_TO_EDGE, ClampToBorder = GL_CLAMP_TO_BORDER };
		enum class Filtering { Nearest = GL_NEAREST, Linear = GL_LINEAR };

	private:

		std::string					name;
		GLuint						id;
		bool						valid;
		std::shared_ptr<bool>		nb_copies;

		static std::vector<Texture>	textures;
		static std::vector<int64_t>	current;

		static void					change_current(const std::vector<const Texture*>& textures);
		static void					unbind();

	public:

									Texture();
									Texture(const Texture& other);
									Texture(const std::string& name, const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::Repeat);
									~Texture();

		void						operator=(const Texture& other);

		bool						load(const std::string& name, const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::Repeat);
		GLuint						get_id() const;
		bool						is_valid() const;

		static bool					add_texture(const Texture& texture);
		static bool					add_texture(const std::string& name, const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::Repeat);
		static Texture*				get_texture(const std::string& name);
		static GLuint				get_id(const std::string& name);

		static void					clear();

		friend						VertexBuffer;
		friend						FrameBuffer;
		friend void					unbind_all();
	};
}

#endif
