#include "dim/dimension3D.hpp"

namespace dim
{
	Scene::Scene(std::string name)
	{
		frame_buffer.create(100, 100);
		render_texture.create(100, 100);
		controller = nullptr;
		this->name = name;
		size = sf::Vector2i(100, 100);
		min  = sf::Vector2i(0, 0);
		max = sf::Vector2i(100, 100);
		resized = false;
		active = false;
		moving = false;
		first_frame = true;
		is_window = false;
		unique_shader = false;
		binded = false;
	}

	Scene::~Scene()
	{
		delete controller;
		controller = nullptr;
	}

	void Scene::check_events(const sf::Event& sf_event)
	{
		if (controller != nullptr)
			controller->check_events(sf_event, *this);
	}

	void Scene::update()
	{
		if (resized)
		{
			frame_buffer.set_size(size.x, size.y);
			render_texture.create(size.x, size.y);
			camera.set_resolution(size.x, size.y);

			camera2D.set_resolution(size.x, size.y);
			render_texture.setView(camera2D.get_view());

			fixed_camera2D.set_resolution(size.x, size.y);
		}

		if (controller != nullptr)
			controller->update(*this);

		if (unique_shader)
		{
			shader.bind();
			shader.send_uniform("u_camera", camera.get_position());
			shader.send_uniform("u_light", lights);
			shader.unbind();
		}
	}

	void Scene::bind() const
	{
		frame_buffer.bind();
		binded = true;
	}

	void Scene::unbind() const
	{
		frame_buffer.unbind();
		binded = false;
	}

	void Scene::set_controller(const Controller& controller)
	{
		this->controller = controller.clone();
	}

	unsigned int Scene::get_width() const
	{
		return size.x;
	}

	unsigned int Scene::get_height() const
	{
		return size.y;
	}

	FrameBuffer Scene::get_frame_buffer() const
	{
		return frame_buffer;
	}

	bool Scene::is_active() const
	{
		return active;
	}

	bool Scene::is_moving() const
	{
		return moving;
	}

	bool Scene::is_resized() const
	{
		return resized;
	}

	void Scene::set_shader(const Shader& shader)
	{
		this->shader = shader;
		unique_shader = true;
	}

	bool Scene::is_in(const Vector2& position) const
	{
		return position.x >= min.x && position.x <= max.x && position.y >= min.y && position.y <= max.y;
	}

	sf::Vector2i Scene::get_center() const
	{
		return sf::Vector2i((min.x + max.x) / 2, (min.y + max.y) / 2);
	}

	void Scene::clear(const Color& color)
	{
		if (!binded)
			frame_buffer.bind();

		frame_buffer.clear(color);
		frame_buffer.unbind();

		render_texture.clear(color.to_sf());

		if (binded)
			frame_buffer.bind();
	}

	void Scene::draw(const sf::Drawable& drawable, bool fixed)
	{
		if (fixed)
			render_texture.setView(fixed_camera2D.get_view());

		render_texture.draw(drawable);

		if (fixed)
			render_texture.setView(camera2D.get_view());
	}

	void Scene::draw(const Object& object, DrawType draw_type)
	{
		if (!binded)
			frame_buffer.bind();

		object.draw(camera, lights, draw_type, unique_shader);

		if (!binded)
			frame_buffer.unbind();
	}

	void Scene::draw(const VertexBuffer& vertex_buffer, DrawType draw_type)
	{
		if (!binded)
			frame_buffer.bind();

		vertex_buffer.draw(draw_type);

		if (!binded)
			frame_buffer.unbind();
	}

	void Scene::display()
	{
		if (binded)
			frame_buffer.unbind();

		// SFML

		render_texture.display();

		// ImGui

		ImGui::Begin(name.data());

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		sf::Vector2i temp = size;

		if (first_frame || size.x != viewportPanelSize.x || size.y != viewportPanelSize.y)
		{
			size.x = viewportPanelSize.x;
			size.y = viewportPanelSize.y;

			resized = true;
		}

		else
			resized = false;

		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		ImVec2 vPos = ImGui::GetWindowPos();

		moving = min.x != vMin.x + vPos.x || min.y != vMin.y + vPos.y || max.x != vMax.x + vPos.x || max.y != vMax.y + vPos.y;

		min.x = vMin.x + vPos.x;
		min.y = vMin.y + vPos.y;
		max.x = vMax.x + vPos.x;
		max.y = vMax.y + vPos.y;

		active = ImGui::IsWindowFocused();

		ImGui::SetCursorPos(ImVec2(8, 27));

		uint64_t textureID = frame_buffer.get_texture().get_id();
		ImGui::Image(textureID, ImVec2{ (float)temp.x, (float)temp.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::SetCursorPos(ImVec2(8, 27));

		ImGui::Image(render_texture.getTexture().getNativeHandle(),
			ImVec2{ (float)render_texture.getTexture().getSize().x, (float)render_texture.getTexture().getSize().y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();

		first_frame = false;

		if (binded)
			frame_buffer.bind();
	}
}
