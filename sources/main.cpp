#include <dim/dimension3D.hpp>

int main()
{
	dim::Window::open("App", 0.75f);
	dim::Scene scene("Scene");

	// Camera
	scene.set_controller(dim::OrbitController());

	dim::PerspectiveCamera cam;
	cam.set_position(dim::Vector3(0.f, 0.f, 3.f));
	scene.set_camera(cam);

	// Lights
	scene.add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f), dim::Color(1.f, 1.f, 1.f)));

	// Objects
	dim::Object object_1(dim::Mesh::Sphere(256, 256), dim::Material(dim::Color(1.f, 0.1f, 0.1f), 0.1f, 0.5f, 0.6f, 30.f));

	dim::Object object_2(dim::Mesh::Cone(256), dim::Material(dim::Color(0.1f, 1.f, 0.1f), 0.1f, 0.5f, 0.6f, 30.f));
	object_2.move(dim::Vector3(1.1f, 0.f, 0.f));

	dim::Object object_3(dim::Mesh::Cylinder(256), dim::Material(dim::Color(0.1f, 0.1f, 1.f), 0.1f, 0.5f, 0.6f, 30.f));
	object_3.move(dim::Vector3(-1.1f, 0.f, 0.f));

	// Buttons info
	float color[4] = { 1.f, 1.f, 1.f, 1.f };

	// Main loop
	while (dim::Window::running)
	{
		// Dimension3D
		sf::Event sf_event;
		while (dim::Window::get_window().pollEvent(sf_event))
		{
			dim::Window::check_events(sf_event);
			scene.check_events(sf_event);
		}

		dim::Window::clear();
		scene.clear();

		dim::Window::update();
		scene.update();

		scene.draw(object_1);
		scene.draw(object_2);
		scene.draw(object_3);

		scene.display();

		// ImGui
		ImGui::Begin("Menu");
		ImGui::Button("Button");
		ImGui::ColorPicker3("Color picker", color, ImGuiColorEditFlags_PickerHueWheel);
		ImGui::End();

		// Dimension3D
		dim::Window::display();
	}

	dim::shut_down();
	return EXIT_SUCCESS;
}
