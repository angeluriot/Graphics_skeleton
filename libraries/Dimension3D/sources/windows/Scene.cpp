#include "dim/dimension3D.h"

namespace dim
{
	Scene Scene::window = Scene(true, true);

	Scene::Scene(bool window, bool null)
	{
		name = "";
		resized = false;
		active = false;
		moving = false;
		first_frame = true;
		is_window = true;
	}

	Scene::Scene(std::string name)
	{
		frame_buffer.create(100, 100);
		this->name = name;
		size = sf::Vector2i(100, 100);
		min  = sf::Vector2i(0, 0);
		max = sf::Vector2i(100, 100);
		resized = false;
		active = false;
		moving = false;
		first_frame = true;
		is_window = false;
	}

	bool Scene::operator==(const Scene& other) const
	{
		return name == other.name && is_window == other.is_window;
	}

	bool Scene::operator!=(const Scene& other) const
	{
		return !(*this == other);
	}

	sf::Vector2i Scene::get_size() const
	{
		return size;
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

	bool Scene::is_in(const Vector2& position)
	{
		return position.x >= min.x && position.x <= max.x && position.y >= min.y && position.y <= max.y;
	}

	void Scene::clear(const sf::Color& color)
	{
		frame_buffer.bind();
		frame_buffer.clear(color);
		frame_buffer.unbind();

		if (resized)
			frame_buffer.set_size(size.x, size.y);
	}

	void Scene::display()
	{
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

		uint64_t textureID = frame_buffer.get_texture().get_id();
		ImGui::Image(textureID, ImVec2{ (float)temp.x, (float)temp.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();

		first_frame = false;
	}
}
