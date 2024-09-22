#ifdef USE_RENDER_RAYLIB
#include "RenderColorSystem.h"

#include <raylib.h>

#include "Components/ScreenPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {}

	void RenderColorSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto& view = _registry.view<Components::ScreenPosition, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::ScreenPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			DrawRectangle(
				position.x,
				position.y,
				static_cast<int>(unitSize),
				static_cast<int>(unitSize),
				Color { renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha }
			);
		}
	}
}
#endif