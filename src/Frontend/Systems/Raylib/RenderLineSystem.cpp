#ifdef USE_RENDER_RAYLIB
#include "RenderLineSystem.h"

#include <raylib.h>
#include <cassert>

#include "Components/RenderPositionSet.h"
#include "Components/RenderLine.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	using namespace Sample::Components;

	RenderLineSystem::RenderLineSystem(entt::registry &registry) : _registry(registry) {}

	void RenderLineSystem::Update() {
		// TODO: sorting layers
		const auto& view = _registry.view<RenderPositionSet, RenderColor, RenderLine>();
		for (auto&& [entity, renderPosition, renderColor] : view.each()) {
			const auto& positions = renderPosition.positions;
			assert(positions.size() >= 2 && "RenderLineSystem::Update: no enough positions!");
			const auto color = Color {
				renderColor.color.red,
				renderColor.color.green,
				renderColor.color.blue,
				renderColor.color.alpha
			};
			for (size_t i = 0; i < positions.size() - 1; ++i) {
				const auto& start = positions[i];
				const auto& end = positions[i + 1];
				DrawLine(
					start.x, start.y,
					end.x, end.y,
					color
				);
			}
		}
	}
}
#endif