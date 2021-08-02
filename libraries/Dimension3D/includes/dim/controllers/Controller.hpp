#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Scene;
	class Camera;

	class Controller
	{
	protected:

		float	sensitivity;
		float	speed;

		virtual Controller* clone() const = 0;

	public:

		enum class Type { Orbit, Fly, Drag };

		Controller();
		Controller(const Controller& other) = default;

		Controller& operator=(const Controller& other) = default;

		virtual Type get_type() const = 0;
		virtual void check_events(const sf::Event& sf_event, Scene& scene) = 0;
		virtual void update(Scene& scene) = 0;

		friend Scene;
	};
}

#endif
