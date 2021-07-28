#include "dim/dimension3D.h"

namespace dim
{
	void FrameBuffer::create(unsigned int witdh, unsigned int height)
	{
		if (nb_copies.unique())
		{
			glDeleteFramebuffers(1, &fbo);
			glDeleteTextures(1, &texture.id);
			glDeleteRenderbuffers(1, &rbo);
		}

		else
		{
			fbo = 0;
			texture.id = 0;
			rbo = 0;
		}

		size = sf::Vector2i(witdh, height);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		{
			glGenTextures(1, &texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

				texture.valid = true;
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		nb_copies = std::make_shared<bool>();
	}

	FrameBuffer::FrameBuffer()
	{
		fbo = 0;
		rbo = 0;
		valid = false;
		size = sf::Vector2i(0, 0);
		nb_copies = std::make_shared<bool>();
	}

	FrameBuffer::FrameBuffer(unsigned int witdh, unsigned int height)
	{
		fbo = 0;
		rbo = 0;
		valid = false;
		size = sf::Vector2i(0, 0);
		nb_copies = std::make_shared<bool>();

		create(witdh, height);
	}

	FrameBuffer::~FrameBuffer()
	{
		if (nb_copies.unique())
		{
			glDeleteFramebuffers(1, &fbo);
			glDeleteTextures(1, &texture.id);
			glDeleteRenderbuffers(1, &rbo);
		}
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glViewport(0, 0, size.x, size.y);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Window::get_width(), Window::get_height());
	}

	Texture FrameBuffer::get_texture() const
	{
		return texture;
	}

	void FrameBuffer::set_size(unsigned int witdh, unsigned int height)
	{
		if (nb_copies.unique())
		{
			glDeleteTextures(1, &texture.id);
			glDeleteRenderbuffers(1, &rbo);
		}

		else
		{
			texture.id = 0;
			rbo = 0;
		}

		size = sf::Vector2i(witdh, height);

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		{
			glGenTextures(1, &texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::clear(const sf::Color& color)
	{
		glViewport(0, 0, size.x, size.y);
		glEnable(GL_DEPTH_TEST);
		glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}
