#ifndef ORTHOGRAPHICCAMERA_HPP
#define ORTHOGRAPHICCAMERA_HPP

#include "dim/cameras/Camera.hpp"

namespace dim
{
	class OrthographicCamera : public Camera
	{
	private:

		float ratio;
		float zoom_level;

		Camera* clone() const override;

	public:

		static constexpr float	default_zoom	= 1.f;

		OrthographicCamera(const OrthographicCamera& other) = default;
		OrthographicCamera(float zoom = default_zoom, float near = default_near, float far = default_far);

		Type get_type() const override;
		void zoom(float zoom);
		void set_zoom(float new_zoom);
		void set_resolution(float width, float height) override;
	};
}

#endif
