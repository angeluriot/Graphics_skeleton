#ifndef SCENE_H
#define SCENE_H

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/opengl/FrameBuffer.hpp"

namespace dim
{
	class Camera;
	class Object;

	class Scene
	{
	private:

		std::string		name;
		FrameBuffer		frame_buffer;
		sf::RenderTexture render_texutre;
		sf::Vector2i	size;
		sf::Vector2i	min;
		sf::Vector2i	max;
		bool			resized;
		bool			active;
		bool			moving;
		bool			first_frame;
		bool			is_window;
		bool			unique_shader;
		Shader			shader;
		mutable bool	binded;

	public:

		Camera				camera;
		std::vector<Light>	lights;

							Scene(const Scene& other) = default;
							Scene(std::string name = "Scene");

		Scene&				operator=(const Scene& other) = default;

		void				check_events(const sf::Event& sf_event);
		void				update();
		void				bind() const;
		void				unbind() const;
		unsigned int		get_width() const;
		unsigned int		get_height() const;
		FrameBuffer			get_frame_buffer() const;
		bool				is_active() const;
		bool				is_moving() const;
		bool				is_resized() const;
		void				set_shader(const Shader& shader);
		bool				is_in(const Vector2& position) const;
		void				clear(const Color& color = Color::Transparent);
		void				draw(const sf::Drawable& drawable);
		void				draw(const Object& object, DrawType draw_type = DrawType::Triangles);
		void				draw(const VertexBuffer& vertex_buffer, DrawType draw_type = DrawType::Triangles);
		void				display();
	};
}

#endif
