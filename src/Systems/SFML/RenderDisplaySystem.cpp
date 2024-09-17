#ifdef USE_RENDER_SFML
#include "RenderDisplaySystem.h"

#include <cassert>

#include "Components/SFML/AppWindow.h"

namespace Sample::Systems::SFML {
	RenderDisplaySystem::RenderDisplaySystem(entt::registry &registry) : _registry(registry) {}

	void RenderDisplaySystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
		auto& window = appWindow.window;

		window.display();
	}
}
#endif