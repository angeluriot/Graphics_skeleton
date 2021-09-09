#include <dim/dimension3D.hpp>

int main()
{
	// Open the main window and initialize the libraries
	dim::Window::open("App", 0.75f);

	// Create the scenes
	dim::Scene scene("Scene");

	// Cameras and controllers
	dim::PerspectiveCamera cam;
	cam.set_position(dim::Vector3(0.f, 0.f, 3.f));
	scene.set_camera(cam);

	scene.set_controller(dim::OrbitController());

	// Add lights
	scene.add_light(dim::DirectionalLight(dim::Vector3(-1.f, -1.f, -1.f)));

	// Create objects
	dim::Object object_1(dim::Mesh::Sphere(256, 256), dim::Material(dim::Color(1.f, 0.1f, 0.1f), 0.1f, 0.5f, 0.6f, 30.f));

	dim::Object object_2(dim::Mesh::Cone(256), dim::Material(dim::Color(0.1f, 1.f, 0.1f), 0.1f, 0.5f, 0.6f, 30.f));
	object_2.move(dim::Vector3(1.1f, 0.f, 0.f));

	dim::Object object_3(dim::Mesh::Cylinder(256), dim::Material(dim::Color(0.1f, 0.1f, 1.f), 0.1f, 0.5f, 0.6f, 30.f));
	object_3.move(dim::Vector3(-1.1f, 0.f, 0.f));

	// The example button color
	float color[4] = { 1.f, 1.f, 1.f, 1.f };

	// Main loop
	while (dim::Window::running)
	{
		// Check events
		sf::Event sf_event;
		while (dim::Window::poll_event(sf_event))
		{
			dim::Window::check_events(sf_event);
			scene.check_events(sf_event);
		}

		// Clear the screen
		dim::Window::clear();
		scene.clear();

		// Update interactive stuff
		dim::Window::update();
		scene.update();

		// Draw the objects
		scene.draw(object_1);
		scene.draw(object_2);
		scene.draw(object_3);

		// Display the scenes to the window
		scene.display();

		// The ImGui window and button example
		ImGui::Begin("Menu");
		ImGui::Button("Button");
		ImGui::ColorPicker3("Color picker", color, ImGuiColorEditFlags_PickerHueWheel);
		ImGui::End();

		// Display the window to the screen
		dim::Window::display();
	}

	// Close the main window and shut down the libraries
	dim::Window::close();
	return EXIT_SUCCESS;
}
