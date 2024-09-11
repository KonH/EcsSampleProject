#ifdef USE_RENDER_SFML
#include "RenderSystem.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <cassert>

#include "Components/Position.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"
#include "Components/SFML/AppWindow.h"

namespace Sample::Systems::SFML {
	RenderSystem::RenderSystem(entt::registry &registry) : _registry(registry) {}

	void RenderSystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
		auto& window = appWindow.window;

		window.clear();

		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto centerX = static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f;
		const auto centerY = static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f;
		const auto rectSize = sf::Vector2f(unitSize, unitSize);
		const auto& view = _registry.view<Components::Position, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::Position>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			sf::RectangleShape rect(rectSize);
			const auto& c = renderColor.color;
			rect.setFillColor(sf::Color(c.red, c.green, c.blue, c.alpha));
			rect.setPosition(sf::Vector2f(
				centerX + static_cast<float>(position.x) * unitSize,
				centerY + static_cast<float>(position.y) * unitSize));

			window.draw(rect);
		}

		window.display();
	}
}
#endif