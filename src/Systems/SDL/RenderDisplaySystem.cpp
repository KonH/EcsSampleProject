#ifdef USE_RENDER_SDL
#include "RenderDisplaySystem.h"

#include <cassert>

#include "Components/SDL/AppWindow.h"

namespace Sample::Systems::SDL {
	RenderDisplaySystem::RenderDisplaySystem(entt::registry &registry) : _registry(registry) {}

	void RenderDisplaySystem::Update() {
		assert(_registry.ctx().contains<Components::SDL::AppWindow>() && "AppWindow singleton not found!");
		const auto& appWindow = _registry.ctx().get<Components::SDL::AppWindow>();
		auto& renderer = appWindow.renderer;

		SDL_RenderPresent(renderer);
	}
}
#endif