#include <dim/dimension3D.hpp>

int main()
{
	dim::Window::open("app", 3.f / 4.f, "resources/icons/icon.png");

	//dim::Shader::add("default", "shaders/color.vert", "shaders/color.frag");
	dim::Shader::add("screen", "shaders/screen.vert", "shaders/screen.frag");

	dim::Texture::add("texture_1", "resources/textures/jojo.jpg");
	dim::Texture::add("texture_2", "resources/textures/rem.png");
	dim::Texture::add("texture_3", "resources/textures/pessi.jpg");
	dim::Texture::add("earth", "resources/textures/earth.jpg");

	//dim::Scene::add("My_scene_1");
	//dim::Scene::add("My_scene_2");

	//dim::Scene& scene_1 = dim::Scene::get("My_scene_1");
	//dim::Scene& scene_2 = dim::Scene::get("My_scene_2");

	//scene_1.set_controller(dim::DragController());
	//scene_2.set_controller(dim::OrbitController());
	dim::Window::set_controller(dim::FlyController());

	dim::PerspectiveCamera cam;
	cam.set_position(dim::Vector3(0.f, 0.f, 1.5f));

	//scene_1.set_camera(cam);
	//scene_2.set_camera(cam);
	dim::Window::set_camera(cam);

	//scene_1.add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f), sf::Color(255, 255, 255)));
	//scene_1.add_light(dim::DirectionalLight(dim::Vector3(1.f, 1.f, -1.f), sf::Color(50, 20, 255)));
	dim::Window::add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f), sf::Color(255, 255, 255)));

	//scene_2.add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f), sf::Color(255, 20, 20)));
	//scene_2.add_light(dim::DirectionalLight(dim::Vector3(1.f, 1.f, -1.f), sf::Color(20, 20, 255)));

	//scene_2.set_post_processing_shader(dim::Shader::get("screen"));
	//scene_1.set_shader(dim::Shader::get("default"));

	dim::Object object_1(dim::Mesh::Sphere(256, 256), dim::Material(sf::Color(255, 50, 50), 0.1f, 0.5f, 0.6f, 30.f));
	object_1.set_texture("earth");
	object_1.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_1.move(dim::Vector3(0.1f, 0.f, 0.f));

	dim::Object object_2(dim::Mesh::empty_square, dim::Material(dim::Color(0.1f, 1.f, 0.1f)));
	//object_2.set_texture("texture_1");
	object_2.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_2.move(dim::Vector3(1.f, 0.f, 0.f));

	dim::Object object_3(dim::Mesh::Cylinder(256), dim::Material(sf::Color(50, 50, 255), 0.1f, 0.5f, 0.6f, 30.f));
	object_3.set_texture("texture_1");
	object_3.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_3.move(dim::Vector3(-1.f, 0.f, 0.f));

	object_1.set_thickness(3.f);
	object_2.set_thickness(6.f);
	object_3.set_thickness(9.f);

	sf::Clock clock;
	clock.restart();
	int fps = 0;
	bool menu_active = false;

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	dim::DrawType type = dim::DrawType::Triangles;

	while (dim::Window::running)
	{
		sf::Event sf_event;
		while (dim::Window::get_window().pollEvent(sf_event))
		{
			dim::Window::check_events(sf_event);
			//dim::Scene::check_all_events(sf_event);
		}

		dim::Window::clear();
		//dim::Scene::clear_all();
		//dim::Scene::update_all();

		dim::Window::get_controller().enable(!menu_active);
		dim::Window::update();

		// Dimension3D

		sf::RectangleShape test_1;
		test_1.setPosition(0, 0);
		test_1.setSize(sf::Vector2f(200, 200));
		test_1.setFillColor(sf::Color::Blue);

		sf::RectangleShape test_2;
		test_2.setPosition(400, 400);
		test_2.setSize(sf::Vector2f(200, 200));
		test_2.setFillColor(sf::Color::Red);

		sf::RectangleShape test_3;
		test_3.setPosition(800, 200);
		test_3.setSize(sf::Vector2f(200, 200));
		test_3.setFillColor(sf::Color::Green);

		dim::Window::draw(object_1, type);
		dim::Window::draw(object_2, type);
		dim::Window::draw(object_3, type);

		dim::Window::draw(test_1);
		dim::Window::draw(test_2, true);
		//scene_2.draw(test_3);

		//dim::Scene::display_all();

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

		static float slider_value;
		static float slider_values[3];
		static float slider_angle;
		static bool check;
		static int current = 3;

		ImGui::SliderFloat("Slider", &slider_value, 0, 500);
		ImGui::SliderFloat3("Slider_2", slider_values, 100, 300);
		ImGui::SliderAngle("Slider_3", &slider_angle);
		ImGui::Checkbox("Check", &check);
		ImGui::Combo("combo", &current, "tomates\0bananes\0courgettes\0pommes\0machins");

		if (clock.getElapsedTime().asSeconds() > 0.3f)
		{
			fps = int(1.f / dim::Window::get_elapsed_time());
			clock.restart();
		}

		menu_active = ImGui::IsWindowFocused();

		ImGui::Text(std::to_string(fps).data());
		//ImGui::Text(("(" + std::to_string(scene_1.get_width()) + " " + std::to_string(scene_1.get_height()) + ")").data());
		ImGui::End();

		// ----------

		dim::Window::display();
	}

	dim::shut_down();
	return EXIT_SUCCESS;
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
