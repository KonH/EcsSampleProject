#ifdef USE_RENDER_RAYLIB
#include "RenderColorSystem.h"

#include <raylib.h>

#include "Components/RenderPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderScale.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {}

	void RenderColorSystem::Update() {
		// TODO: sorting layers
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto& view = _registry.view<Components::RenderPosition, Components::RenderColor>();
		for (const auto& [entity, position, renderColor] : view.each()) {
			auto optionalRenderScale = 1.0f;
			if (const auto &renderScale = _registry.try_get<Components::RenderScale>(entity)) {
				optionalRenderScale = renderScale->scale;
			}
			const auto currentUnitSize = static_cast<int>(unitSize * optionalRenderScale);
			DrawRectangle(
				position.position.x - static_cast<int>(currentUnitSize / 2),
				position.position.y - static_cast<int>(currentUnitSize / 2),
				currentUnitSize,
				currentUnitSize,
				Color { renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha }
			);
		}
	}
}
#endif