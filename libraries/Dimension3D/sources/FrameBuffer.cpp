#include "dim/dimension3D.h"

namespace dim
{
	int64_t FrameBuffer::current = -1;
	FrameBuffer FrameBuffer::default_frame_buffer(true, true);

	FrameBuffer::FrameBuffer(bool priv_1, bool priv_2)
	{
		fbo = 0;
		rbo = 0;
		valid = false;
		nb_copies = std::make_shared<bool>();
	}

	void FrameBuffer::create()
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

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		{
			glGenTextures(1, &texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::get_scene_size().x, Window::get_scene_size().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

				texture.valid = true;
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::get_scene_size().x, Window::get_scene_size().y);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		nb_copies = std::make_shared<bool>();
	}

	void FrameBuffer::change_current(const FrameBuffer& frame_buffer)
	{
		if (current != frame_buffer.fbo)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			current = frame_buffer.fbo;
			glBindFramebuffer(GL_FRAMEBUFFER, current);
		}
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		current = -1;
	}

	void FrameBuffer::clear_default(const sf::Color& color)
	{
		unbind();
		glViewport(0, 0, Window::get_width(), Window::get_height());
		glEnable(GL_DEPTH_TEST);
		glClearColor(14.f / 255.f, 14.f / 255.f, 14.f / 255.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		change_current(default_frame_buffer);
		current;
		glViewport(0, 0, Window::get_scene_size().x, Window::get_scene_size().y);
		glEnable(GL_DEPTH_TEST);
		glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::init()
	{
		default_frame_buffer.create();
	}

	FrameBuffer::FrameBuffer()
	{
		create();
	}

	FrameBuffer::FrameBuffer(const FrameBuffer& other)
	{
		*this = other;
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

	FrameBuffer& FrameBuffer::operator=(const FrameBuffer& other)
	{
		fbo = other.fbo;
		texture = other.texture;
		rbo = other.rbo;
		valid = other.valid;
		nb_copies = other.nb_copies;

		return *this;
	}

	Texture FrameBuffer::get_texture() const
	{
		return texture;
	}

	void FrameBuffer::reload()
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

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		{
			glGenTextures(1, &texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::get_scene_size().x, Window::get_scene_size().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::get_scene_size().x, Window::get_scene_size().y);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::clear()
	{
		change_current(*this);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}
