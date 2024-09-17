#ifdef USE_RENDER_SDL
#include "RenderClearSystem.h"

#include <cassert>

#include "Components/SDL/AppWindow.h"

namespace Sample::Systems::SDL {
	RenderClearSystem::RenderClearSystem(entt::registry &registry) : _registry(registry) {}

	void RenderClearSystem::Update() {
		assert(_registry.ctx().contains<Components::SDL::AppWindow>() && "AppWindow singleton not found!");
		const auto& appWindow = _registry.ctx().get<Components::SDL::AppWindow>();
		auto& renderer = appWindow.renderer;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}
}
#endif