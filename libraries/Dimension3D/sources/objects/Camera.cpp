#include "dim/dimension3D.h"

namespace dim
{
	Camera Camera::null = Camera(true);

	Camera::Camera(bool null)
	{
		scene = nullptr;
		mode = Mode::Free;
		position = Vector3(0.f, 0.f, 0.f);
		sensitivity = 0.f;
		speed = 0.f;
		fov = 45.f;
		view = glm::mat4(1.f);
		projection = glm::mat4(1.f);
		direction = Vector3(0.f, 0.f, -1.f);
		yaw = 0.f;
		pitch = 0.f;
		near = 0.1f;
		far = 100.f;
		moving = false;
		prev_mouse_pos = Vector2();
		prev_mouse_click = false;
		rotation_forbidden = false;
	}

	void Camera::move()
	{
		if (sf::Keyboard::isKeyPressed(left))
			position -= glm::normalize(glm::cross(direction.to_glm(), glm::vec3(0.f, 1.f, 0.f))) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(right))
			position += glm::normalize(glm::cross(direction.to_glm(), glm::vec3(0.f, 1.f, 0.f))) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(forward))
			position += glm::normalize(glm::vec3(direction.to_glm().x, 0., direction.to_glm().z)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(backward))
			position -= glm::normalize(glm::vec3(direction.to_glm().x, 0., direction.to_glm().z)) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(up))
			position += Vector3(0.f, 1.f, 0.f) * speed * Window::elapsed_time;

		if (sf::Keyboard::isKeyPressed(down))
			position -= Vector3(0.f, 1.f, 0.f) * speed * Window::elapsed_time;

		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	void Camera::look()
	{
		yaw += (sf::Mouse::getPosition(Window::get_window()).x - Window::get_width() / 2.f) * sensitivity;
		pitch -= (sf::Mouse::getPosition(Window::get_window()).y - Window::get_height() / 2.f) * sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;

		if (pitch < -89.0f)
			pitch = -89.0f;

		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction = glm::normalize(direction.to_glm());

		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
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
		if ((!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!scene->is_in(sf::Mouse::getPosition(Window::get_window())) || !scene->is_active())) || scene->is_moving())
			rotation_forbidden = true;

		else if (!scene->is_moving() && prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			rotation_forbidden = false;

		if (!scene->is_moving() && scene->is_active() && scene->is_in(sf::Mouse::getPosition(Window::get_window())))
			rotation_forbidden = false;

		if (!scene->is_active())
			rotation_forbidden = true;

		if (!rotation_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			position.set_theta(position.get_theta() - move.x * sensitivity);
			position.set_phi(std::min(std::max(position.get_phi() - move.y * sensitivity, 0.01f), PI - 0.01f));

			view = glm::lookAt(position.to_glm(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	Camera::Camera(Scene& scene, Mode mode, float sensitivity, float fov, float near, float far)
	{
		this->scene = &scene;
		sensitivity = std::max(sensitivity, 0.f);
		fov = std::max(fov, 0.f);
		near = std::max(near, 0.f);
		far = std::max(far, near);

		this->mode = mode;
		position = Vector3(0.f, 0.f, 5.f);
		speed = 0.2f;
		this->sensitivity = (this->mode == Mode::Free ? sensitivity : sensitivity / 40.f);
		this->fov = fov;
		this->near = near;
		this->far = far;

		direction = glm::vec3(0.f, 0.f, -1.f);

		projection = glm::perspective(glm::radians(this->fov), static_cast<float>(Window::get_width()) / static_cast<float>(Window::get_height()), this->near, this->far);
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

		yaw = -90.f;
		pitch = 0.f;
		moving = true;
		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = false;
		rotation_forbidden = false;

		if (this->mode == Mode::Free)
		{
			speed = 2.f;
			sf::Mouse::setPosition(sf::Vector2i(dim::Window::get_width() / 2.f, dim::Window::get_height() / 2.f), dim::Window::get_window());
			Window::get_window().setMouseCursorVisible(false);
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}

		forward = default_forward;
		left = default_left;
		right = default_right;
		backward = default_backward;
		up = default_up;
		down = default_down;
	}

	void Camera::check_events(const sf::Event& sf_event)
	{
		if (mode == Mode::Free && ((sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Escape)
			|| (!moving && sf_event.type == sf::Event::MouseButtonReleased && scene->is_in(sf::Mouse::getPosition(Window::get_window())))))
		{
			moving = !moving;
			sf::Mouse::setPosition(sf::Vector2i(dim::Window::get_width() / 2.f, dim::Window::get_height() / 2.f), dim::Window::get_window());
			Window::get_window().setMouseCursorVisible(!moving);

			if (moving)
				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}

		if (mode == Mode::Rotation && sf_event.type == sf::Event::MouseWheelMoved && scene->is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			position.set_norm(std::max(position.get_norm() - sf_event.mouseWheel.delta * speed, 0.01f));
			view = glm::lookAt(position.to_glm(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void Camera::update()
	{
		if (scene->is_resized())
		{
			if (*scene == Scene::window)
				set_resolution(Window::get_width(), Window::get_height());

			else
				set_resolution(scene->get_size().x, scene->get_size().y);
		}

		if (mode == Mode::Free)
			free_move();

		else
			rotation_move();
	}

	glm::mat4 Camera::get_matrix() const
	{
		return projection * view;
	}

	Camera::Mode Camera::get_mode() const
	{
		return mode;
	}

	void Camera::set_mode(Mode mode)
	{
		if (this->mode == Mode::Free && mode == Mode::Rotation)
		{
			speed /= 10.f;
			sensitivity /= 40.f;
		}

		if (this->mode == Mode::Rotation && mode == Mode::Free)
		{
			speed *= 10.f;
			sensitivity *= 40.f;
		}

		this->mode = mode;

		if (this->mode == Mode::Rotation)
		{
			direction = normalized(-position);
			pitch = asin(-direction.y);
			yaw = atan2(direction.x, direction.z);
		}

		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

		if (this->mode == Mode::Free)
		{
			sf::Mouse::setPosition(sf::Vector2i(dim::Window::get_width() / 2.f, dim::Window::get_height() / 2.f), dim::Window::get_window());
			Window::get_window().setMouseCursorVisible(false);
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}
	}

	Vector3 Camera::get_position() const
	{
		return position;
	}

	void Camera::set_position(const Vector3& position)
	{
		this->position = position;

		if (mode == Mode::Rotation)
		{
			direction = normalized(-position);
			pitch = asin(-direction.y);
			yaw = atan2(direction.x, direction.z);
		}

		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	float Camera::get_sensitivity() const
	{
		return sensitivity;
	}

	void Camera::set_sensitivity(float sensitivity)
	{
		this->sensitivity = std::max(sensitivity, 0.f);
	}

	float Camera::get_speed() const
	{
		return speed;
	}

	void Camera::set_speed(float speed)
	{
		this->speed = std::max(speed, 0.f);
	}

	float Camera::get_fov() const
	{
		return fov;
	}

	void Camera::set_fov(float fov)
	{
		this->fov = std::max(fov, 0.f);
		projection = glm::perspective(glm::radians(this->fov), static_cast<float>(Window::get_width()) / static_cast<float>(Window::get_height()), near, far);
	}

	Vector3 Camera::get_direction() const
	{
		return direction;
	}

	void Camera::set_direction(Vector3 direction)
	{
		if (mode == Mode::Free && direction != Vector3::null)
		{
			this->direction = normalized(direction);
			pitch = asin(-this->direction.y);
			yaw = atan2(this->direction.x, this->direction.z);
		}
	}

	float Camera::get_yaw() const
	{
		return yaw;
	}

	float Camera::get_pitch() const
	{
		return pitch;
	}

	void Camera::set_controls(sf::Keyboard::Key forward, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key backward, sf::Keyboard::Key up, sf::Keyboard::Key down)
	{
		this->forward = forward;
		this->left = left;
		this->right = right;
		this->backward = backward;
		this->up = up;
		this->down = down;
	}

	void Camera::set_resolution(float width, float height)
	{
		if (width > 0.f && height > 0.f)
			projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}
}
