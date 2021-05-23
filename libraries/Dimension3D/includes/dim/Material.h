#ifndef MATERIAL_H
#define MATERIAL_H

#include "dim/libraries.h"

namespace dim
{
	class Material
	{
	private:

		sf::Color			color;
		float				ambient;
		float				diffuse;
		float				specular;
		float				shininess;

	public:

		static Material		default_material;

							Material();
							Material(const Material& other);
							Material(const sf::Color& color, float ambient, float diffuse, float specular, float shininess);

		void				operator=(const Material& other);

		sf::Color			get_color() const;
		void				set_color(const sf::Color& color);
		float				get_ambient() const;
		void				set_ambient(float ambient);
		float				get_diffuse() const;
		void				set_diffuse(float diffuse);
		float				get_specular() const;
		void				set_specular(float specular);
		float				get_shininess() const;
		void				set_shininess(float shininess);
	};
}

#endif
