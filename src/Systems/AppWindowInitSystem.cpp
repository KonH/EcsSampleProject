#include "AppWindowInitSystem.h"

#include "Components/AppWindow.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems {
	AppWindowInitSystem::AppWindowInitSystem(entt::registry &registry) : _registry(registry) {}

	void AppWindowInitSystem::Init() {
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();

		const auto modelSize = sf::Vector2u(renderSettings.screenWidth, renderSettings.screenHeight);
		auto& appWindow = _registry.ctx().emplace<Components::AppWindow>();
		appWindow.window.create(sf::VideoMode(modelSize), renderSettings.windowTitle);
	}
}