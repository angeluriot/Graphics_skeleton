#ifndef CAMERA_H
#define CAMERA_H

#include "dim/libraries.h"
#include "dim/Window.h"

namespace dim
{
	class Camera
	{
	public:

		enum class Mode { Free, Rotation };

	private:

		Mode				mode;
		Vector3				position;
		float				speed;
		float				sensitivity;
		float				fov;
		glm::mat4			view;
		glm::mat4			projection;
		glm::vec3			up;
		glm::vec3			front;
		float				yaw;
		float				pitch;
		bool				moving;
		Vector2				prev_mouse_pos;
		bool				prev_mouse_click;
		bool				rotation_forbidden;

		void				move();
		void				look();
		void				free_move();
		void				rotation_move();

	public:

							Camera(const Camera& other);
							Camera(Mode mode = Mode::Rotation);

		void				operator=(const Camera& other);

		void				check_events(const sf::Event& sf_event);
		void				update();
		glm::mat4			get_mvp() const;
		Mode				get_mode() const;
		void				set_mode(Mode mode);
		Vector3				get_position() const;
		void				set_position(const Vector3& position);
		float				get_fov() const;
		void				set_fov(float fov);
		float				get_sensitivity() const;
		void				set_sensitivity(float sensitivity);
		float				get_speed() const;
		void				set_speed(float speed);

		// TODO changer les touches
	};
}

#endif
