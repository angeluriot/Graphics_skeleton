#ifndef UTILS_H
#define UTILS_H

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector2.hpp"

namespace dim
{
	constexpr float	pi = 3.14159265359f; // Pi
}

/*
class Simulation;
class Restart;

#define	FREE_THREAD	2	// Nombre de threads libres
#define	FPS_BUTTONS	10	// Nombre de millisecondes entre chaque updates des buttons

// Classe de gestion d'�v�nements

class My_event
{
public:

	sf::RenderWindow* window;	// Fen�tre SFML
	Simulation* simulation;		// Simulation
	Restart* restart_button;	// Pointeur vers le bouton restart
	bool* end;					// Fin de la simulation
	bool* simulation_end;		// La simulation

	My_event();
	My_event(const My_event& sf);
	My_event(sf::RenderWindow* window, Simulation* simulation, Restart* restart_button, bool* end, bool* simulation_end);

	void				operator=(const My_event& sf);

	bool				events(sf::Event& sf_event);
	bool				check();
	bool				wait();
};

uint32_t				random_int(int32_t min, int32_t max);
float					random_float(const float& min, const float& max);
bool					rand_probability(const float& probability);
bool					sleep_every(uint16_t milliseconds);
*/
#endif
