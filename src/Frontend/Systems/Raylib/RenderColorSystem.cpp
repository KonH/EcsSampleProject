#ifdef USE_RENDER_RAYLIB
#include "RenderColorSystem.h"

#include <raylib.h>

#include "Components/RenderPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderScale.h"
#include "Components/RenderLayer.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	RenderColorSystem::RenderColorSystem(entt::registry &registry) : _registry(registry) {
		const auto group =
				_registry.group<Components::RenderPosition, Components::RenderColor, Components::RenderLayer>();
		group.sort<Components::RenderLayer>(
				[](const Components::RenderLayer &a, const Components::RenderLayer &b) { return a.layer < b.layer; });
	}

	void RenderColorSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto group = _registry.group<Components::RenderPosition, Components::RenderColor, Components::RenderLayer>();
		for (const auto entity: group) {
			const auto& position = _registry.get<Components::RenderPosition>(entity);
			const auto& renderColor = _registry.get<Components::RenderColor>(entity);
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