#include <dim/dimension3D.hpp>

namespace dim
{
	void init_opengl()
	{
		glewExperimental = GL_TRUE;
		glewInit();

		glViewport(0, 0, Window::get_width(), Window::get_height());
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
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
		Shader::init();
	}

	void shut_down()
	{
		ImGui::SFML::Shutdown();
		Window::close();
	}
}
