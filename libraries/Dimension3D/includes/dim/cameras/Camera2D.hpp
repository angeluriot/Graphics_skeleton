#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Camera2D
	{
	private:

		sf::View view;
		float zoom_level;
		Vector2 size;

	public:

				Camera2D();
				Camera2D(const Camera2D& other) = default;

		Camera2D& operator=(const Camera2D& other) = default;

		void	set_zoom(float new_zoom);
		void	set_rotation(float new_angle);
		void	set_position(const Vector2& new_position);

		void	zoom(float zoom);
		void	rotate(float angle);
		void	move(const Vector2& movement);

		void	set_resolution(float width, float height);
		sf::View& get_view();
		float	get_zoom() const;
		Vector2 get_resolution() const;
	};
}

#endif
