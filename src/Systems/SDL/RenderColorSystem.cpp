#ifdef USE_RENDER_SDL
#include "RenderColorSystem.h"

#include <cassert>

#include "Components/WorldPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"
#include "Components/SDL/AppWindow.h"

namespace Sample::Systems::SDL {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {}

	void RenderColorSystem::Update() {
		assert(_registry.ctx().contains<Components::SDL::AppWindow>() && "AppWindow singleton not found!");
		const auto& appWindow = _registry.ctx().get<Components::SDL::AppWindow>();
		const auto& renderer = appWindow.renderer;

		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = static_cast<int>(renderSettings.unitSize);
		const auto centerX = static_cast<int>(static_cast<float>(renderSettings.screenWidth) / 2.f - static_cast<float>(unitSize) / 2.f);
		const auto centerY = static_cast<int>(static_cast<float>(renderSettings.screenHeight) / 2.f - static_cast<float>(unitSize) / 2.f);
		const auto& view = _registry.view<Components::WorldPosition, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::WorldPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			SDL_Rect rect;
			rect.w = unitSize;
			rect.h = unitSize;
			rect.x = centerX + position.x * unitSize;
			rect.y = centerY + position.y * unitSize;
			SDL_SetRenderDrawColor(renderer, renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
#endif