#ifdef USE_RENDER_SFML
#include "RenderClearSystem.h"

#include <cassert>

#include "Components/SFML/AppWindow.h"

namespace Sample::Systems::SFML {
	RenderClearSystem::RenderClearSystem(entt::registry &registry) : _registry(registry) {}

	void RenderClearSystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
		auto& window = appWindow.window;

		window.clear();
	}
}
#endif