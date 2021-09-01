#include <dim/dimension3D.hpp>

int main()
{
	dim::Window::open("App", 0.75f, "resources/icons/icon.png");

	dim::Texture::add("earth", "resources/textures/earth.jpg");

	dim::Scene::add("Scene");
	dim::Scene& scene = dim::Scene::get("Scene");

	scene.set_controller(dim::OrbitController());

	dim::PerspectiveCamera cam;
	cam.set_position(dim::Vector3(0.f, 0.f, 3.f));

	scene.set_camera(cam);
	scene.add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f), dim::Color(1.f, 1.f, 1.f)));

	dim::Object object_1(dim::Mesh::Sphere(256, 256), dim::Material(sf::Color(255, 50, 50), 0.1f, 0.5f, 0.6f, 30.f));
	object_1.set_texture("earth");
	object_1.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_1.rotate(180.f, dim::Vector3(0.f, 1.f, 0.f));
	object_1.move(dim::Vector3(0.f, 0.f, 0.f));

	dim::Object object_2(dim::Mesh::Cone(256), dim::Material(dim::Color(0.1f, 1.f, 0.1f), 0.1f, 0.5f, 0.6f, 30.f));
	object_2.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_2.move(dim::Vector3(1.1f, 0.f, 0.f));

	dim::Object object_3(dim::Mesh::Cylinder(256), dim::Material(sf::Color(50, 50, 255), 0.1f, 0.5f, 0.6f, 30.f));
	object_3.set_size(dim::Vector3(1.f, 1.f, 1.f));
	object_3.move(dim::Vector3(-1.1f, 0.f, 0.f));

	sf::Clock clock;
	clock.restart();
	int fps = 0;

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	dim::DrawType type = dim::DrawType::Triangles;

	while (dim::Window::running)
	{
		sf::Event sf_event;
		while (dim::Window::get_window().pollEvent(sf_event))
		{
			dim::Window::check_events(sf_event);
			dim::Scene::check_all_events(sf_event);
		}

		// Dimension3D

		dim::Window::clear();
		dim::Scene::clear_all();

		dim::Window::update();
		dim::Scene::update_all();

		scene.draw(object_1, type);
		scene.draw(object_2, type);
		scene.draw(object_3, type);

		dim::Scene::display_all();

		// ImGui

		ImGui::Begin("Menu");

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

		ImGui::Text(std::to_string(fps).data());
		ImGui::Text(("(" + std::to_string(scene.get_width()) + " " + std::to_string(scene.get_height()) + ")").data());
		ImGui::End();

		// ----------

		dim::Window::display();
	}

	dim::shut_down();
	return EXIT_SUCCESS;
}
