#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "dim/utils/libraries.h"
#include "dim/opengl/Texture.h"

namespace dim
{
	class FrameBuffer
	{
	public: // Remettre private

		GLuint					fbo;
		Texture					texture;
		GLuint					rbo;
		bool					valid;
		sf::Vector2i			size;
		std::shared_ptr<bool>	nb_copies;

		void					create(unsigned int witdh, unsigned int height);

	public:

								FrameBuffer();
								FrameBuffer(const FrameBuffer& other) = default;
								FrameBuffer(unsigned int witdh, unsigned int height);
								~FrameBuffer();

		FrameBuffer&			operator=(const FrameBuffer& other) = default;

		void					bind();
		static void				unbind();
		Texture					get_texture() const;
		void					set_size(unsigned int witdh, unsigned int height);
		void					clear(const sf::Color& color = sf::Color::Transparent);
	};
}

#endif
