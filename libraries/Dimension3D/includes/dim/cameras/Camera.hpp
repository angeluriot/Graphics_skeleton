#ifndef CAMERA_H
#define CAMERA_H

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/windows/Window.hpp"

namespace dim
{
	class Scene;

	class Camera
	{
	public:

		enum class Mode { Free, Rotation };

	private:

		Mode				mode;
		Vector3				position;
		float				sensitivity;
		float				speed;
		float				fov;
		glm::mat4			view;
		glm::mat4			projection;
		Vector3				direction;
		float				yaw;
		float				pitch;
		float				near;
		float				far;
		bool				moving;
		Vector2				prev_mouse_pos;
		bool				prev_mouse_click;
		bool				rotation_forbidden;
		sf::Keyboard::Key	forward;
		sf::Keyboard::Key	left;
		sf::Keyboard::Key	right;
		sf::Keyboard::Key	backward;
		sf::Keyboard::Key	up;
		sf::Keyboard::Key	down;

							Camera(bool null);

		void				move();
		void				look();
		void				free_move();
		void				rotation_move(const Scene& scene);

	public:

		static constexpr float				default_fov			= 45.f;
		static constexpr float				default_sensitivity	= 0.2f;
		static constexpr float				default_near		= 0.1f;
		static constexpr float				default_far			= 100.f;
		static constexpr sf::Keyboard::Key	default_forward		= sf::Keyboard::Key::Z;
		static constexpr sf::Keyboard::Key	default_left		= sf::Keyboard::Key::Q;
		static constexpr sf::Keyboard::Key	default_right		= sf::Keyboard::Key::D;
		static constexpr sf::Keyboard::Key	default_backward	= sf::Keyboard::Key::S;
		static constexpr sf::Keyboard::Key	default_up			= sf::Keyboard::Key::Space;
		static constexpr sf::Keyboard::Key	default_down		= sf::Keyboard::Key::LControl;

		static Camera null;

					Camera(const Camera& other) = default;
					Camera(Mode mode = Mode::Rotation, float sensitivity = default_sensitivity, float fov = default_fov, float near = default_near, float far = default_far);

		Camera&		operator=(const Camera& other) = default;

		void		check_events(const sf::Event& sf_event, const Scene& scene);
		void		update(const Scene& scene);
		glm::mat4	get_matrix() const;
		Mode		get_mode() const;
		void		set_mode(Mode mode);
		Vector3		get_position() const;
		void		set_position(const Vector3& position);
		float		get_sensitivity() const;
		void		set_sensitivity(float sensitivity);
		float		get_speed() const;
		void		set_speed(float speed);
		float		get_fov() const;
		void		set_fov(float fov);
		Vector3		get_direction() const;
		void		set_direction(Vector3 direction);
		float		get_yaw() const;
		float		get_pitch() const;
		void		set_controls(sf::Keyboard::Key forward, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key backward, sf::Keyboard::Key up, sf::Keyboard::Key down);
		void		set_resolution(float width, float height);
	};
}

#endif
