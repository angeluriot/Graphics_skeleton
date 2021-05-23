#include "Simulation.h"

int main()
{
	dim::Window::create_relative("app", 3.f / 4.f, 16.f / 9.f, true, "resources/icons/icon.png");

	std::vector<float> positions_1 =
	{
		-1.f,  -0.5f, 0.f,
		 0.f,  -0.5f, 0.f,
		-0.5f,  0.5f, 0.f
	};

	std::vector<float> normals_1 =
	{
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f
	};

	std::vector<float> uvs_1 =
	{
		0.f,  1.f,
		0.5f, 0.f,
		1.f,  1.f
	};

	std::vector<float> positions_2 =
	{
		 0.f,  -0.5f, 0.f,
		 1.0f, -0.5f, 0.f,
		 0.5f,  0.5f, 0.f
	};

	std::vector<float> normals_2 =
	{
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f
	};

	std::vector<float> uvs_2 =
	{
		0.f,  1.f,
		0.5f, 0.f,
		1.f,  1.f
	};

	dim::Shader::add_shader("default", "shaders/color.vert", "shaders/color.frag");
	dim::Shader::add_shader("screen", "shaders/screen.vert", "shaders/screen.frag");

	dim::Texture::add_texture("texture_1", "resources/textures/jojo.jpg");
	dim::Texture::add_texture("texture_2", "resources/textures/rem.png");
	dim::Texture::add_texture("texture_3", "resources/textures/pessi.jpg");

	/*
	dim::Mesh geometry_1;
	geometry_1.set_positions(positions_1);
	geometry_1.set_normals(normals_1);
	geometry_1.set_uvs(uvs_1);

	dim::Mesh geometry_2;
	geometry_2.set_positions(positions_2);
	geometry_2.set_normals(normals_2);
	geometry_2.set_uvs(uvs_2);

	dim::VertexBuffer vertex_object_1("color");
	vertex_object_1.send_data(geometry_1);
	vertex_object_1.add_texture("texture_1");

	dim::VertexBuffer vertex_object_2("color");
	vertex_object_2.send_data(geometry_2);
	vertex_object_2.add_texture("texture_2");
	*/

	dim::Camera camera(dim::Camera::Mode::Rotation);
	dim::Light light_1(dim::Light::Type::Directional, sf::Color(255, 50, 50), 1., dim::Vector3(-1.f, -1.f, -1.f).get_normalized());
	dim::Light light_2(dim::Light::Type::Directional, sf::Color(50, 50, 255), 1., dim::Vector3(1.f, 1.f, -1.f).get_normalized());

	dim::Object object_1(dim::Mesh::cube, dim::Material(sf::Color(255, 10, 10), 0.1f, 0.5f, 0.6f, 30.f));
	object_1.set_texture("texture_3");
	object_1.set_local_scale(dim::Vector3(1.f, 1.f, 1.f));
	object_1.move(dim::Vector3(0.f, 0.f, 0.f));

	dim::Object object_2(dim::Mesh::sphere_64, dim::Material(sf::Color(255, 10, 10), 0.1f, 0.5f, 0.6f, 30.f));
	object_2.set_texture("texture_1");
	object_2.set_local_scale(dim::Vector3(1.f, 1.f, 1.f));
	object_2.move(dim::Vector3(2.f, 0.f, 0.f));

	dim::Object object_3(dim::Mesh::sphere_64, dim::Material(sf::Color(255, 10, 10), 0.1f, 0.5f, 0.6f, 30.f));
	object_3.set_texture("texture_2");
	object_3.set_local_scale(dim::Vector3(1.f, 1.f, 1.f));
	object_3.move(dim::Vector3(-2.f, 0.f, 0.f));

	dim::VertexBuffer vbo_test("screen");
	vbo_test.send_data(dim::Mesh::screen);

	sf::Clock clock;
	clock.restart();
	int fps = 0;

	//object_1.add_child(object_2);
	//object_2.add_child(object_3);

	//glm::mat4 model = glm::mat4(1.f);

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	dim::DrawType type = dim::DrawType::Triangles;

	while (dim::Window::running)
	{
		sf::Event sf_event;
		while (dim::Window::get_window().pollEvent(sf_event))
		{
			dim::Window::check_events(sf_event);
			camera.check_events(sf_event);
		}

		dim::Window::clear();

		// Dimension3D

		camera.update();

		object_1.draw(camera, { &light_1, &light_2 }, type);
		object_2.draw(camera, { &light_1, &light_2 }, type);
		object_3.draw(camera, { &light_1, &light_2 }, type);

		// ----------

		dim::unbind_all();

		// SFML



		// ImGui

		ImGui::Begin("Hello, world!");
		if (ImGui::Button("Look at this pretty button"))
		{
			if (type == dim::DrawType::Points)
				type = dim::DrawType::Lines;

			else if (type == dim::DrawType::Lines)
				type = dim::DrawType::Triangles;

			else
				type = dim::DrawType::Points;
		}

		ImGui::ColorPicker3("color_2", color, ImGuiColorEditFlags_PickerHueWheel);

		if (clock.getElapsedTime().asSeconds() > 0.3f)
		{
			fps = int(1.f / dim::Window::clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		ImGui::Text(std::to_string(fps).data());
		ImGui::End();

		// ----------

		dim::Window::display();
	}

	dim::shut_down();
	return 0;
}

/*
A RETENIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!

void renderingThread(sf::Window* window)
{
	// activation du contexte de la fenêtre
	window->setActive(true);

	// la boucle de rendu
	while (window->isOpen())
	{
		// dessin...

		// fin de la trame -- ceci est une fonction de rendu (elle a besoin d'activer le contexte)
		window->display();
	}
}

int main()
{
	// création de la fenêtre (souvenez-vous: créer la fenêtre dans le thread principal est plus sûr, du fait des limitations de l'OS)
	sf::Window window(sf::VideoMode(800, 600), "OpenGL");

	// désactivation de son contexte OpenGL
	window.setActive(false);

	// lancement du thread de rendu
	sf::Thread thread(&renderingThread, &window);
	thread.Launch();

	// la boucle d'évènements/logique/etc.
	while (window.isOpen())
	{
		...
	}

	return 0;
}*/
