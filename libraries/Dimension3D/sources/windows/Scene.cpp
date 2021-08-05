#include "dim/dimension3D.hpp"

namespace dim
{
	Scene::Scene(std::string name)
	{
		frame_buffer.create(100, 100);
		render_texture.create(100, 100);
		controller = nullptr;
		camera = nullptr;
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
		post_processing = false;
	}

	Scene::~Scene()
	{
		delete controller;
		controller = nullptr;

		delete camera;
		camera = nullptr;
	}

	void Scene::check_events(const sf::Event& sf_event)
	{
		if (controller != nullptr && camera != nullptr)
			controller->check_events(sf_event, *this, *camera);
	}

	void Scene::update()
	{
		if (resized)
		{
			frame_buffer.set_size(size.x, size.y);
			render_texture.create(size.x, size.y);

			if (camera != nullptr)
				camera->set_resolution(size.x, size.y);

			camera2D.set_resolution(size.x, size.y);
			render_texture.setView(camera2D.get_view());

			fixed_camera2D.set_resolution(size.x, size.y);
		}

		if (controller != nullptr && camera != nullptr)
			controller->update(*this, *camera);

		if (unique_shader)
		{
			shader.bind();

			if (camera != nullptr)
				shader.send_uniform("u_camera", camera->get_position());

			else
				shader.send_uniform("u_camera", Vector3(0.f, 0.f, -1.f));

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

	void Scene::set_camera(const Camera& camera)
	{
		this->camera = camera.clone();
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

	void Scene::set_post_processing_shader(const Shader& shader)
	{
		post_processing_shader = shader;
		screen.send_data(shader, Mesh::screen, DataType::Positions | DataType::TexCoords);
		post_processing = true;
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

	void Scene::add_light(const Light& light)
	{
		lights.push_back(light.clone());
	}

	void Scene::display()
	{
		if (post_processing)
		{
			if (!binded)
				frame_buffer.bind();

			post_processing_shader.bind();
			frame_buffer.get_texture().bind();
			screen.bind();

			post_processing_shader.send_uniform("u_texture", frame_buffer.get_texture());

			screen.draw();

			screen.unbind();
			frame_buffer.get_texture().unbind();
			post_processing_shader.unbind();

			if (!binded)
				frame_buffer.unbind();
		}

		if (binded)
			frame_buffer.unbind();

		// SFML

		render_texture.display();

		// ImGui

		ImGui::SetNextWindowSizeConstraints(ImVec2(50, 50), ImVec2(10000, 10000));
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(name.data(), NULL, windowFlags);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		sf::Vector2i temp = size;

		if (first_frame || size.x != viewportPanelSize.x || size.y != viewportPanelSize.y)
		{
			size.x = static_cast<int>(viewportPanelSize.x);
			size.y = static_cast<int>(viewportPanelSize.y);

			resized = true;
		}

		else
			resized = false;

		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		ImVec2 vPos = ImGui::GetWindowPos();

		moving = min.x != vMin.x + vPos.x || min.y != vMin.y + vPos.y || max.x != vMax.x + vPos.x || max.y != vMax.y + vPos.y;

		min.x = static_cast<int>(vMin.x + vPos.x);
		min.y = static_cast<int>(vMin.y + vPos.y);
		max.x = static_cast<int>(vMax.x + vPos.x);
		max.y = static_cast<int>(vMax.y + vPos.y);

		active = ImGui::IsWindowFocused();

		ImGui::SetCursorPos(ImVec2(8, 27));

		unsigned int textureID = frame_buffer.get_texture().get_id();
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
