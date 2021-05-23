#include "dim/dimension3D.h"

namespace dim
{
	void Camera::move()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			position -= glm::normalize(glm::cross(front, up)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			position += glm::normalize(glm::cross(front, up)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			position += glm::normalize(glm::vec3(front.x, 0., front.z)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			position -= glm::normalize(glm::vec3(front.x, 0., front.z)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			position += up * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			position -= up * speed * Window::elapsed_time;

		view = glm::lookAt(position.to_glm(), position.to_glm() + front, up);
	}

	void Camera::look()
	{
		yaw += (sf::Mouse::getPosition(Window::get_window()).x - Window::get_width() / 2.f) * sensitivity;
		pitch -= (sf::Mouse::getPosition(Window::get_window()).y - Window::get_height() / 2.f) * sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;

		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);

		view = glm::lookAt(position.to_glm(), position.to_glm() + front, up);
	}

	void Camera::free_move()
	{
		if (moving)
		{
			move();
			look();
			sf::Mouse::setPosition(sf::Vector2i(Window::get_width() / 2.f, Window::get_height() / 2.f), Window::get_window());
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}
	}

	void Camera::rotation_move()
	{
		if ((!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!is_in_scene(sf::Mouse::getPosition(Window::get_window())) || !Window::scene_active)) || Window::scene_moving)
			rotation_forbidden = true;

		else if (!Window::scene_moving && prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			rotation_forbidden = false;

		if (!Window::scene_moving && Window::scene_active && is_in_scene(sf::Mouse::getPosition(Window::get_window())))
			rotation_forbidden = false;

		if (!Window::scene_active)
			rotation_forbidden = true;

		if (!rotation_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			position.set_theta(position.get_theta() - move.x * sensitivity);
			position.set_phi(std::min(std::max(position.get_phi() - move.y * sensitivity, 0.01f), PI - 0.01f));

			view = glm::lookAt(position.to_glm(), glm::vec3(0.f, 0.f, 0.f), up);
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	Camera::Camera(const Camera& other)
	{
		*this = other;
	}

	Camera::Camera(Mode mode)
	{
		this->mode = mode;
		position = Vector3(0.f, 0.f, 5.f);
		speed = 0.2f;
		fov = 45.f;
		up = glm::vec3(0.f, 1.f, 0.f);
		front = glm::vec3(0.f, 0.f, -1.f);
		sensitivity = 0.005f;

		projection = glm::perspective(glm::radians(fov), float(Window::get_width()) / float(Window::get_height()), 0.1f, 100.f);
		view = glm::lookAt(this->position.to_glm(), this->position.to_glm() + front, up);

		yaw = -90.f;
		pitch = 0.f;
		moving = true;
		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = false;
		rotation_forbidden = false;

		if (this->mode == Mode::Free)
		{
			speed = 2.f;
			sensitivity = 0.1f;
			moving = true;
			sf::Mouse::setPosition(sf::Vector2i(dim::Window::get_width() / 2.f, dim::Window::get_height() / 2.f), dim::Window::get_window());
			Window::get_window().setMouseCursorVisible(false);
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}
	}

	void Camera::operator=(const Camera& other)
	{
		mode = other.mode;
		position = other.position;
		speed = other.speed;
		sensitivity = other.sensitivity;
		fov = other.fov;
		view = other.view;
		projection = other.projection;
		up = other.up;
		front = other.front;
		yaw = other.yaw;
		pitch = other.pitch;
		moving = other.moving;
		prev_mouse_pos = other.prev_mouse_pos;
		prev_mouse_click = other.prev_mouse_click;
		rotation_forbidden = other.rotation_forbidden;
	}

	void Camera::check_events(const sf::Event& sf_event)
	{
		if (mode == Mode::Free && ((sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Escape)
			|| (!moving && sf_event.type == sf::Event::MouseButtonReleased && is_in_scene(sf::Mouse::getPosition(Window::get_window())))))
		{
			moving = !moving;
			sf::Mouse::setPosition(sf::Vector2i(dim::Window::get_width() / 2.f, dim::Window::get_height() / 2.f), dim::Window::get_window());
			Window::get_window().setMouseCursorVisible(!moving);

			if (moving)
				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}

		if (mode == Mode::Rotation && sf_event.type == sf::Event::MouseWheelMoved && is_in_scene(sf::Mouse::getPosition(Window::get_window())))
		{
			position.set_norm(std::max(position.get_norm() - sf_event.mouseWheel.delta * speed, 0.01f));
			view = glm::lookAt(position.to_glm(), glm::vec3(0.f, 0.f, 0.f), up);
		}
	}

	void Camera::update()
	{
		if (Window::is_resized)
			projection = glm::perspective(glm::radians(fov), float(Window::get_scene_size().x) / float(Window::get_scene_size().y), 0.1f, 100.f);

		if (mode == Mode::Free)
			free_move();

		else
			rotation_move();
	}

	glm::mat4 Camera::get_mvp() const
	{
		return projection * view;
	}

	Camera::Mode Camera::get_mode() const
	{
		return mode;
	}

	void Camera::set_mode(Mode mode)
	{
		this->mode = mode;

		// TODO
	}

	Vector3 Camera::get_position() const
	{
		return position;
	}

	void Camera::set_position(const Vector3& position)
	{
		this->position = position;
	}

	float Camera::get_fov() const
	{
		return fov;
	}

	void Camera::set_fov(float fov)
	{
		this->fov = fov;
	}

	float Camera::get_sensitivity() const
	{
		return sensitivity;
	}

	void Camera::set_sensitivity(float sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	float Camera::get_speed() const
	{
		return speed;
	}

	void Camera::set_speed(float speed)
	{
		this->speed = speed;
	}
}
