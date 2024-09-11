#ifdef USE_RENDER_SDL
#include "AppWindowInitSystem.h"

#include <SDL.h>

#include "Components/SDL/AppWindow.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::SDL {
	AppWindowInitSystem::AppWindowInitSystem(entt::registry &registry) : _registry(registry) {}

	void AppWindowInitSystem::Init() {
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();
		auto& appWindow = _registry.ctx().emplace<Components::SDL::AppWindow>();
		appWindow.window = SDL_CreateWindow(
			renderSettings.windowTitle.c_str(), // Window title
			static_cast<int>(renderSettings.screenWidth), // Width
			static_cast<int>(renderSettings.screenHeight), // Height
			0
		);

		if (appWindow.window == nullptr) {
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return;
		}

		appWindow.renderer = SDL_CreateRenderer(appWindow.window, nullptr);
		if (appWindow.renderer == nullptr) {
			SDL_Log("Failed to create renderer: %s", SDL_GetError());
			return;
		}
	}
}
#endif