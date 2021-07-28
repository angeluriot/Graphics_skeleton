#ifndef SCENE_H
#define SCENE_H

#include "dim/utils/libraries.h"
#include "dim/utils/utils.h"
#include "dim/opengl/FrameBuffer.h"

namespace dim
{
	class Scene
	{
	private:

		FrameBuffer		frame_buffer;
		std::string		name;
		sf::Vector2i	size;
		sf::Vector2i	min;
		sf::Vector2i	max;
		bool			resized;
		bool			active;
		bool			moving;
		bool			first_frame;
		bool			is_window;

		Scene(bool window, bool null);

	public:

		static Scene window;

		Scene(const Scene& other) = default;
		Scene(std::string name = "Scene");

		Scene& operator=(const Scene& other) = default;
		bool operator==(const Scene& other) const;
		bool operator!=(const Scene& other) const;

		sf::Vector2i get_size() const;
		FrameBuffer get_frame_buffer() const;
		bool is_active() const;
		bool is_moving() const;
		bool is_resized() const;

		bool is_in(const Vector2& position);
		void clear(const sf::Color& color = sf::Color::Transparent);
		void display();
	};
}

#endif
