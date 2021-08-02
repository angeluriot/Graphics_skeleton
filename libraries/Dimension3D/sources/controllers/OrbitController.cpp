#include "dim/dimension3D.hpp"

namespace dim
{
	Controller* OrbitController::clone() const
	{
		return new OrbitController(*this);
	}

	OrbitController::OrbitController(float sensitivity, float speed)
	{
		this->sensitivity = sensitivity;
		this->speed = speed;
		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = false;
		rotation_forbidden = false;
	}

	Controller::Type OrbitController::get_type() const
	{
		return Type::Orbit;
	}

	void OrbitController::check_events(const sf::Event& sf_event, Scene& scene)
	{
		if (sf_event.type == sf::Event::MouseWheelMoved && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			scene.camera.position.set_norm(std::max(scene.camera.position.get_norm() - sf_event.mouseWheel.delta * speed, 0.01f));
			scene.camera.view = glm::lookAt(scene.camera.position.to_glm(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void OrbitController::update(Scene& scene)
	{
		if ((!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!scene.is_in(sf::Mouse::getPosition(Window::get_window())) ||
			!scene.is_active())) || scene.is_moving())
			rotation_forbidden = true;

		else if (!scene.is_moving() && prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			rotation_forbidden = false;

		if (!scene.is_moving() && scene.is_active() && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
			rotation_forbidden = false;

		if (!scene.is_active())
			rotation_forbidden = true;

		if (!rotation_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			scene.camera.position.set_theta(scene.camera.position.get_theta() - move.x * sensitivity);
			scene.camera.position.set_phi(std::min(std::max(scene.camera.position.get_phi() - move.y * sensitivity, 0.01f), pi - 0.01f));

			scene.camera.view = glm::lookAt(scene.camera.position.to_glm(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}
}
