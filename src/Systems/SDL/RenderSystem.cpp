#ifdef USE_RENDER_SDL
#include "RenderSystem.h"

#include <cassert>

#include "Components/Position.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"
#include "Components/SDL/AppWindow.h"

namespace Sample::Systems::SDL {
	RenderSystem::RenderSystem(entt::registry &registry) : _registry(registry) {}

	void RenderSystem::Update() {
		assert(_registry.ctx().contains<Components::SDL::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SDL::AppWindow>();
		auto& window = appWindow.window;
		auto& renderer = appWindow.renderer;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto centerX = static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f;
		const auto centerY = static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f;
		const auto& view = _registry.view<Components::Position, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::Position>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			SDL_FRect rect;
			rect.w = unitSize;
			rect.h = unitSize;
			rect.x = centerX + static_cast<float>(position.x) * unitSize;
			rect.y = centerY + static_cast<float>(position.y) * unitSize;
			SDL_SetRenderDrawColor(renderer, renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha);
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
	}
}
#endif