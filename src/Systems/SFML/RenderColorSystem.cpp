#ifdef USE_RENDER_SFML
#include "RenderColorSystem.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <cassert>

#include "Utils.h"
#include "Components/WorldPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"
#include "Components/SFML/AppWindow.h"

namespace Sample::Systems::SFML {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {}

	void RenderColorSystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
		auto& window = appWindow.window;

		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto centerX = static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f;
		const auto centerY = static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f;
		const auto rectSize = sf::Vector2f(unitSize, unitSize);
		const auto& view = _registry.view<Components::WorldPosition, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::WorldPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			sf::RectangleShape rect(rectSize);
			const auto& c = renderColor.color;
			rect.setFillColor(Utils::ConvertColor(c));
			rect.setPosition(sf::Vector2f(
				centerX + static_cast<float>(position.x) * unitSize,
				centerY + static_cast<float>(position.y) * unitSize));

			window.draw(rect);
		}
	}
}
#endif