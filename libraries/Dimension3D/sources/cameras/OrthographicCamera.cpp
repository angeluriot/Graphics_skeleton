#include "dim/dimension3D.hpp"

namespace dim
{
	Camera* OrthographicCamera::clone() const
	{
		return new OrthographicCamera(*this);
	}

	OrthographicCamera::OrthographicCamera(float zoom, float near, float far) : Camera()
	{
		zoom_level = zoom;
		this->near = near;
		this->far = far;
		ratio = 1.f;

		projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
	}

	Camera::Type OrthographicCamera::get_type() const
	{
		return Type::Orthographic;
	}

	void OrthographicCamera::zoom(float zoom)
	{
		zoom_level *= 1.f - (zoom - 1.f);
		projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
	}

	void OrthographicCamera::set_zoom(float new_zoom)
	{
		zoom_level = 1.f - (new_zoom - 1.f);
		projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
	}

	void OrthographicCamera::set_resolution(float width, float height)
	{
		if (width > 0.f && height > 0.f)
		{
			ratio = width / height;
			projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
		}
	}
}
