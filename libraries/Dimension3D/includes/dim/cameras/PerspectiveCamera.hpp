#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

#include "dim/cameras/Camera.hpp"

namespace dim
{
	class PerspectiveCamera : public Camera
	{
	private:

		float fov;

		Camera* clone() const override;

	public:

		static constexpr float	default_fov		= 45.f;

		PerspectiveCamera(const PerspectiveCamera& other) = default;
		PerspectiveCamera(float fov = default_fov, float near = default_near, float far = default_far);

		Type get_type() const override;
		void set_resolution(float width, float height) override;
	};
}

#endif
