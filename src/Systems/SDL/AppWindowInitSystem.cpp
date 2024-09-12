#ifdef USE_RENDER_SDL
#include "AppWindowInitSystem.h"

#include <SDL.h>

#include "Components/SDL/AppWindow.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::SDL {
	AppWindowInitSystem::AppWindowInitSystem(entt::registry &registry) : _registry(registry) {}

	void AppWindowInitSystem::Init() {
		SDL_Log("Initializing SDL AppWindow: started");
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();
		auto& appWindow = _registry.ctx().emplace<Components::SDL::AppWindow>();
		appWindow.window = SDL_CreateWindow(
			renderSettings.windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			static_cast<int>(renderSettings.screenWidth),
			static_cast<int>(renderSettings.screenHeight),
			SDL_WINDOW_SHOWN
		);

		if (appWindow.window == nullptr) {
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return;
		}

		appWindow.renderer = SDL_CreateRenderer(appWindow.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (appWindow.renderer == nullptr) {
			SDL_Log("Failed to create renderer: %s", SDL_GetError());
			return;
		}
		SDL_Log("Initializing SDL AppWindow: finished");
	}
}
#endif