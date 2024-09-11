#ifdef USE_RENDER_SFML
#include "AppWindowInitSystem.h"

#include "Components/SFML/AppWindow.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::SFML {
	AppWindowInitSystem::AppWindowInitSystem(entt::registry &registry) : _registry(registry) {}

	void AppWindowInitSystem::Init() {
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();

		const auto modelSize = sf::Vector2u(renderSettings.screenWidth, renderSettings.screenHeight);
		auto& appWindow = _registry.ctx().emplace<Components::SFML::AppWindow>();
		appWindow.window.create(sf::VideoMode(modelSize), renderSettings.windowTitle);
	}
}
#endif