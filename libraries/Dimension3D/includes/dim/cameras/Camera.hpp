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
	protected:

		Vector3				position;
		glm::mat4			view;
		glm::mat4			projection;
		Vector3				direction;
		float				yaw;
		float				pitch;
		float				near;
		float				far;

		virtual Camera*		clone() const = 0;

	public:

		enum class Type { Perspective, Orthographic };

		static constexpr float	default_near	= 0.1f;
		static constexpr float	default_far		= 100.f;

					Camera();
					Camera(const Camera& other) = default;

		Camera&		operator=(const Camera& other) = default;

		virtual Type	get_type() const = 0;
		glm::mat4	get_matrix() const;
		Vector3		get_position() const;
		void		set_position(const Vector3& position);
		Vector3		get_direction() const;
		void		set_direction(Vector3 direction);
		void		set_direction(float yaw, float pitch);
		float		get_yaw() const;
		float		get_pitch() const;
		virtual void	set_resolution(float width, float height) = 0;

		friend		Controller;
		friend		OrbitController;
		friend		FlyController;
		friend		DragController;
		friend		Scene;
	};
}

#endif
