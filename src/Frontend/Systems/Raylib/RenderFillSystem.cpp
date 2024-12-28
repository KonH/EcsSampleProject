#ifdef USE_RENDER_RAYLIB
#include "RenderFillSystem.h"

#include <raylib.h>

#include "Components/RenderFill.h"
#include "Components/RenderPosition.h"
#include "Components/RenderColor.h"
#include "Components/RenderScale.h"
#include "Components/RenderLayer.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	using namespace Sample::Components;

	RenderFillSystem::RenderFillSystem(entt::registry &registry) : _registry(registry) {
		const auto group = _registry.group<RenderFill, RenderPosition, RenderColor, RenderLayer>();
		group.sort<RenderLayer>(
				[](const RenderLayer &a, const RenderLayer &b) { return a.layer < b.layer; });
	}

	void RenderFillSystem::Update() {
		const auto renderSettings = _registry.ctx().get<RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto group = _registry.group<RenderFill, RenderPosition, RenderColor, RenderLayer>();
		for (auto&& [entity, position, renderColor, _]: group.each()) {
			auto optionalRenderScale = 1.0f;
			if (const auto &renderScale = _registry.try_get<RenderScale>(entity)) {
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