#include "dim/dimension3D.hpp"

namespace dim
{
	Camera::Camera()
	{
		position = Vector3(0.f, 0.f, 5.f);
		direction = glm::vec3(0.f, 0.f, -1.f);

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
}
