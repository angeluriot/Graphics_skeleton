#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "dim/libraries.h"
#include "dim/Texture.h"

namespace dim
{
	class FrameBuffer
	{
	public: // Remettre private

		GLuint					fbo;
		Texture					texture;
		GLuint					rbo;
		bool					valid;
		std::shared_ptr<bool>	nb_copies;

		static int64_t			current;
		static FrameBuffer		default_frame_buffer;

								FrameBuffer(bool priv_1, bool priv_2);

		void					create();

		static void				change_current(const FrameBuffer& frame_buffer);
		static void				unbind();
		static void				clear_default(const sf::Color& color);
		static void				init();

	public:

								FrameBuffer();
								FrameBuffer(const FrameBuffer& other);
								~FrameBuffer();

		FrameBuffer&			operator=(const FrameBuffer& other);

		Texture					get_texture() const;
		void					reload();
		void					clear();
	};
}

#endif
