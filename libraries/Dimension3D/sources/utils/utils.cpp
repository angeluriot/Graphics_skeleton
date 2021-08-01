#include "dim/dimension3D.hpp"

/*
sf::RenderWindow* window;
uint16_t screen_width;

// Construit un gestionnaire d'�v�nement

My_event::My_event()
{
	window = NULL;
	simulation = NULL;
	restart_button = NULL;
	end = NULL;
	simulation_end = NULL;
}

// Construit un gestionnaire d'�v�nement � partir d'un autre

My_event::My_event(const My_event& sf)
{
	*this = sf;
}

// Construit un gestionnaire d'�v�nement � partir des pointeurs qu'il utilise

My_event::My_event(sf::RenderWindow* window, Simulation* simulation, Restart* restart_button, bool* end, bool* simulation_end)
{
	this->window = window;
	this->simulation = simulation;
	this->restart_button = restart_button;
	this->end = end;
	this->simulation_end = simulation_end;
}

// Assignation

void My_event::operator=(const My_event& sf)
{
	window = sf.window;
	simulation = sf.simulation;
	restart_button = sf.restart_button;
	end = sf.end;
	simulation_end = sf.simulation_end;
}

// Gestion des diff�rents types d'�v�nements

bool My_event::events(sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Closed)
	{
		*end = true;
		return true;
	}

	if (restart_button->is_active)
	{
		if (restart_button->update(*window))
		{
			*simulation_end = true;
			window->clear(sf::Color::Black);
			simulation->draw();
			restart_button->draw(*window);
			window->display();
			return true;
		}

		window->clear(sf::Color::Black);
		simulation->draw();
		restart_button->draw(*window);
		window->display();
	}

	return false;
}

// V�rifie si un �v�nement se produit

bool My_event::check()
{
	static sf::Event sf_event;

	window->pollEvent(sf_event);

	if (events(sf_event))
		return true;

	return false;
}

// Attend qu'un �v�nement se produit

bool My_event::wait()
{
	static sf::Event sf_event;

	window->waitEvent(sf_event);

	return events(sf_event);
}

// Donne un entier entre min et max

uint32_t random_int(int32_t min, int32_t max)
{
	return rand() % (max - min) + min;
}

// Donne un r�el entre min et max

float random_float(const float& min, const float& max)
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min) + min;
}

// Donne "vrai" avec une probabilit� choisie

bool rand_probability(const float& probability)
{
	if (probability < 0.f)
		return false;

	if (probability < 1.f)
		return (rand() / static_cast<float>(RAND_MAX) < probability);

	return true;
}

// G�re les fps

bool sleep_every(uint16_t milliseconds)
{
	static sf::Clock clock;

	if (clock.getElapsedTime() >= sf::milliseconds(milliseconds))
	{
		clock.restart();
		return true;
	}

	else
		return false;
}
*/
