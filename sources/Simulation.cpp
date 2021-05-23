#include "Simulation.h"

// Cr�e une simulation

Simulation::Simulation()
{
	restart();
}

// Recrr�e une simulation � partir des donn�es du menu

void Simulation::restart()
{
	void_image.create(dim::Window::get_width(), dim::Window::get_height(), sf::Color(0, 0, 0));
	image = void_image;

	texture.create(dim::Window::get_width(), dim::Window::get_height());

	render_texture.create(dim::Window::get_width(), dim::Window::get_height());
	render_texture.clear(sf::Color::Black);
	render_texture.display();

	this->window = window;

	draw_simulation();
}

// Affiche la simulation

void Simulation::draw_simulation()
{
}

// Met � jour la simulation

void Simulation::update()
{
}

// Affiche la simulation

void Simulation::draw()
{
	//texture.update(image);
	//window->draw(sf::Sprite(texture));

	render_texture.display();
	window->draw(sf::Sprite(render_texture.getTexture()));
}
