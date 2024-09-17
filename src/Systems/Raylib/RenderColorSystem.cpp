#ifdef USE_RENDER_RAYLIB
#include "RenderColorSystem.h"

#include <raylib.h>

#include "Components/WorldPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {}

	void RenderColorSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto centerX = static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f;
		const auto centerY = static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f;
		const auto& view = _registry.view<Components::WorldPosition, Components::RenderColor>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::WorldPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);

			DrawRectangle(
				static_cast<int>(centerX + static_cast<float>(position.x) * unitSize),
				static_cast<int>(centerY + static_cast<float>(position.y) * unitSize),
				static_cast<int>(unitSize),
				static_cast<int>(unitSize),
				Color { renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha }
			);
		}
	}
}
#endif