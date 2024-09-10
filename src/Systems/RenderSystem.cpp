#include "RenderSystem.h"

#include <cassert>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Components/AppWindow.h"
#include "Components/Position.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems {
	RenderSystem::RenderSystem(entt::registry &registry) : _registry(registry) {}

	void RenderSystem::Update() {
		assert(_registry.ctx().contains<Components::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::AppWindow>();
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
			rect.setFillColor(renderColor.color);
			rect.setPosition(sf::Vector2f(
				centerX + static_cast<float>(position.x) * unitSize,
				centerY + static_cast<float>(position.y) * unitSize));

			window.draw(rect);
		}

		window.display();
	}
}