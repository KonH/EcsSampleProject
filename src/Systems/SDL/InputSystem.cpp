#ifdef USE_RENDER_SDL
#include "InputSystem.h"

#include <cassert>

#include "Components/Runtime.h"
#include "Components/SDL/AppWindow.h"

namespace Sample::Systems::SDL {
	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {}

	void InputSystem::Update() {
		assert(_registry.ctx().contains<Components::SDL::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SDL::AppWindow>();
		auto& window = appWindow.window;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				_registry.ctx().get<Components::Runtime>().isRunning = false;
				SDL_DestroyWindow(window);
			}
		}
	}
}
#endif