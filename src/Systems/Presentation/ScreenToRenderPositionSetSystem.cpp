#include "ScreenToRenderPositionSetSystem.h"

#include "Components/ScreenPositionSet.h"
#include "Components/ScreenOffset.h"
#include "Components/RenderPositionSet.h"

namespace Sample::Systems::Presentation {
	// TODO: potential unwanted system? (if offset is not used for sets)
	ScreenToRenderPositionSetSystem::ScreenToRenderPositionSetSystem(entt::registry &registry) : _registry(registry) {}

	void ScreenToRenderPositionSetSystem::Update() {
		const auto view = _registry.view<Components::ScreenPositionSet, Components::RenderPositionSet>();
		for (auto [entity, screenPosition, renderPosition] : view.each()) {
			auto offset = Types::Vector2Int { 0, 0 };
			if (_registry.any_of<Components::ScreenOffset>(entity)) {
				const auto& screenOffset = _registry.get<Components::ScreenOffset>(entity);
				offset = screenOffset.offset;
			}
			auto& screenPositions = screenPosition.positions;
			auto& renderPositions = renderPosition.positions;
			if (renderPositions.size() != screenPositions.size()) {
				renderPositions.clear();
				renderPositions.resize(screenPositions.size());
			}
			for (auto i = 0; i < screenPositions.size(); ++i) {
				renderPositions[i] = screenPositions[i] + offset;
			}
		}
	}
}