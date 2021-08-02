#ifndef CAMERA_H
#define CAMERA_H

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/windows/Window.hpp"

namespace dim
{
	class Scene;
	class Controller;
	class OrbitController;
	class FlyController;
	class DragController;

	class Camera
	{
	private:

		Vector3				position;
		float				fov;
		glm::mat4			view;
		glm::mat4			projection;
		Vector3				direction;
		float				yaw;
		float				pitch;
		float				near;
		float				far;

	public:

		static constexpr float				default_fov			= 45.f;
		static constexpr float				default_near		= 0.1f;
		static constexpr float				default_far			= 100.f;

					Camera(const Camera& other) = default;
					Camera(float fov = default_fov, float near = default_near, float far = default_far);

		Camera&		operator=(const Camera& other) = default;

		glm::mat4	get_matrix() const;
		Vector3		get_position() const;
		void		set_position(const Vector3& position);
		float		get_fov() const;
		void		set_fov(float fov);
		Vector3		get_direction() const;
		void		set_direction(Vector3 direction);
		void		set_direction(float yaw, float pitch);
		float		get_yaw() const;
		float		get_pitch() const;
		void		set_resolution(float width, float height);

		friend		Controller;
		friend		OrbitController;
		friend		FlyController;
		friend		DragController;
	};
}

#endif
