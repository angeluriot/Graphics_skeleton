#ifndef ORBITCONTROLLER_HPP
#define ORBITCONTROLLER_HPP

#include "dim/controllers/Controller.hpp"

namespace dim
{
	class OrbitController : public Controller
	{
	private:

		Vector2	prev_mouse_pos;
		bool	prev_mouse_click;
		bool	rotation_forbidden;

		static constexpr float default_sensitivity = 0.005f;
		static constexpr float default_speed = 0.2f;

		Controller* clone() const override;

	public:

				OrbitController(float sensitivity = default_sensitivity, float speed = default_speed);
				OrbitController(const OrbitController& other) = default;

		OrbitController& operator=(const OrbitController& other) = default;

		Type	get_type() const override;
		void	check_events(const sf::Event& sf_event, Scene& scene) override;
		void	update(Scene& scene) override;
	};
}

#endif
