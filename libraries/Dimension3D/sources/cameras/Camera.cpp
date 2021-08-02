#include "dim/dimension3D.hpp"

namespace dim
{
	Camera::Camera(float fov, float near, float far)
	{
		fov = std::max(fov, 0.f);
		near = std::max(near, 0.f);
		far = std::max(far, near);

		position = Vector3(0.f, 0.f, 5.f);
		this->fov = fov;
		this->near = near;
		this->far = far;

		direction = glm::vec3(0.f, 0.f, -1.f);

		projection = glm::perspective(glm::radians(this->fov), static_cast<float>(Window::get_width()) / static_cast<float>(Window::get_height()), this->near, this->far);
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

		yaw = -90.f;
		pitch = 0.f;
	}

	glm::mat4 Camera::get_matrix() const
	{
		return projection * view;
	}

	Vector3 Camera::get_position() const
	{
		return position;
	}

	void Camera::set_position(const Vector3& position)
	{
		this->position = position;
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
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
		if (direction != Vector3::null)
		{
			this->direction = normalized(direction);
			pitch = asin(-this->direction.y);
			yaw = atan2(this->direction.x, this->direction.z);

			view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void Camera::set_direction(float yaw, float pitch)
	{
		this->yaw = yaw;
		this->pitch = pitch;

		if (this->pitch > 89.0f)
			this->pitch = 89.0f;

		if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction = glm::normalize(direction.to_glm());

		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	float Camera::get_yaw() const
	{
		return yaw;
	}

	float Camera::get_pitch() const
	{
		return pitch;
	}

	void Camera::set_resolution(float width, float height)
	{
		if (width > 0.f && height > 0.f)
			projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}
}
