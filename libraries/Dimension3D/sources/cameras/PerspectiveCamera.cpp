#include "dim/dimension3D.hpp"

namespace dim
{
	Camera* PerspectiveCamera::clone() const
	{
		return new PerspectiveCamera(*this);
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float near, float far) : Camera()
	{
		this->fov = fov;
		this->near = near;
		this->far = far;

		projection = glm::perspective(glm::radians(this->fov), static_cast<float>(Window::get_width()) / static_cast<float>(Window::get_height()), this->near, this->far);
	}

	Camera::Type PerspectiveCamera::get_type() const
	{
		return Type::Perspective;
	}

	void PerspectiveCamera::set_resolution(float width, float height)
	{
		if (width > 0.f && height > 0.f)
			projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}
}
