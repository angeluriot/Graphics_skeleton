#include "dim/dimension3D.hpp"

namespace dim
{
	Camera2D::Camera2D()
	{
		zoom_level = 1.f;
		size = Vector2(100, 100);
		view = sf::View((size / 2.f).to_sf_float(), size.to_sf_float());
	}

	void Camera2D::set_zoom(float new_zoom)
	{
		zoom_level = new_zoom;
		view.setSize(zoom_level * size.to_sf_float());
	}

	void Camera2D::set_rotation(float new_angle)
	{
		view.setRotation(new_angle);
	}

	void Camera2D::set_position(const Vector2& new_position)
	{
		view.setCenter(new_position.to_sf_float() * zoom_level);
	}

	void Camera2D::zoom(float zoom)
	{
		zoom_level *= zoom;
		view.setSize(zoom_level * size.to_sf_float());
	}

	void Camera2D::rotate(float angle)
	{
		view.rotate(angle);
	}

	void Camera2D::move(const Vector2& movement)
	{
		view.move(movement.to_sf_float());
	}

	void Camera2D::set_resolution(float width, float height)
	{
		move((Vector2(width, height) - size) * 0.5f * zoom_level);

		size = Vector2(width, height);
		view.setSize(zoom_level * size.to_sf_float());
	}

	sf::View& Camera2D::get_view()
	{
		return view;
	}

	float Camera2D::get_zoom() const
	{
		return zoom_level;
	}

	Vector2 Camera2D::get_resolution() const
	{
		return size;
	}
}
