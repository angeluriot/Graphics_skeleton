#include <dim/dimension3D.h>

namespace dim
{
	void init_opengl()
	{
		glewExperimental = GL_TRUE;
		glewInit();

		glViewport(0, 0, Window::get_width(), Window::get_height());
		glClearColor(14.f / 255.f, 14.f / 255.f, 14.f / 255.f, 1.f);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDepthRange(0.f, 1.f);
	}

	void init_imgui()
	{
		ImGui::SFML::Init(Window::get_window());
		ImGui::StyleColorsDark();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}

	void init()
	{
		init_opengl();
		init_imgui();
		Shader::load_default();
	}

	void unbind_all()
	{
		VertexBuffer::unbind();
		Texture::unbind();
		Shader::unbind();
		FrameBuffer::unbind();
	}

	void shut_down()
	{
		unbind_all();
		ImGui::SFML::Shutdown();
		Window::close();
		Texture::clear();
		Shader::clear();
	}
}
