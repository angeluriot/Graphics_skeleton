#ifndef WINDOW_H
#define WINDOW_H

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Camera;
	class Light;

	class Window // RAJOUTER DE QUOI faire sa propre fen�tre !!!!!!!
	{
	public: // CHANGER APRES !!!!!!!!!!

		static sf::RenderWindow*	window;			// Pointeur vers la fen�tre
		static float				screen_coef;	// Co�fficient en fonction de la taille de l'�cran par rapport au 1080p
		static sf::Clock			clock;
		static float				elapsed_time;

	public: // CHANGER APRES !!!!!!!!!!

		static bool					running;		// Hauteur de la fen�tre

	public:

		static void					create_relative(const std::string& project_name, float screen_ratio = 3.f / 4.f, float window_ratio = 16.f / 9.f,
													bool resizable = false, const std::string& icon_path = "");
		static void					create_absolute(const std::string& project_name, uint16_t width = 1920, uint16_t height = 1080, bool resizable = false,
													const std::string& icon_path = "");
		static sf::RenderWindow&	get_window();
		static uint16_t				get_width();
		static uint16_t				get_height();
		static void					clear(const Color& color = Color(0.05f, 0.05f, 0.05f, 1.f));
		static void					draw(const sf::Drawable& drawable);
		static void					display();
		static void					close();
		static uint16_t				to_relative(uint16_t position);
		static void					check_events(const sf::Event& sf_event);

		friend						Camera;
	};

	sf::RenderWindow&	get_window();
	uint16_t			to_relative(uint16_t position);
	bool				is_in_window(const Vector2& position);
	bool				is_on_border_window(const Vector2& position);
}

#endif
