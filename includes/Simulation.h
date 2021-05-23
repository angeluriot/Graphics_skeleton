#ifndef SIMULATION_H
#define SIMULATION_H

#include <dim/dimension3D.h>

// Classe d�finissant la simulation

class Simulation
{
public:

	sf::Image			void_image;		// Image vide
	sf::Image			image;			// Image � afficher
	sf::Texture			texture;		// Texture supportant l'image
	sf::RenderTexture	render_texture;	// Texture � afficher
	sf::RenderWindow*	window;			// Pointeur sur la fen�tre

	Simulation();

	void restart();
	void draw_simulation();
	void update();
	void draw();
};

#endif
