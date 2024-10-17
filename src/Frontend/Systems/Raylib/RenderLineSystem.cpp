#ifdef USE_RENDER_RAYLIB
#include "RenderLineSystem.h"

#include <raylib.h>
#include <cassert>

#include "Components/RenderPositionSet.h"
#include "Components/RenderLine.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	RenderLineSystem::RenderLineSystem(entt::registry &registry) : _registry(registry) {}

	void RenderLineSystem::Update() {
		// TODO: sorting layers
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto& view = _registry.view<Components::RenderPositionSet, Components::RenderLine>();
		for (auto [entity, renderPosition, renderLine] : view.each()) {
			const auto& positions = renderPosition.positions;
			assert(positions.size() >= 2 && "RenderLineSystem::Update: no enough positions!");
			const auto color = Color {
				renderLine.color.red,
				renderLine.color.green,
				renderLine.color.blue,
				renderLine.color.alpha
			};
			for (auto i = 0; i < positions.size() - 1; ++i) {
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