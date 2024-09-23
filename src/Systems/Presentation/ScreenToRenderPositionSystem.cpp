#include "ScreenToRenderPositionSystem.h"

#include "Components/ScreenPosition.h"
#include "Components/ScreenOffset.h"
#include "Components/RenderPosition.h"

namespace Sample::Systems::Presentation {
	ScreenToRenderPositionSystem::ScreenToRenderPositionSystem(entt::registry &registry) : _registry(registry) {}

	void ScreenToRenderPositionSystem::Update() {
		auto view = _registry.view<Components::ScreenPosition, Components::RenderPosition>();
		for (auto [entity, screenPosition, renderPosition] : view.each()) {
			auto offset = Types::Vector2Int { 0, 0 };
			if (_registry.any_of<Components::ScreenOffset>(entity)) {
				const auto& screenOffset = _registry.get<Components::ScreenOffset>(entity);
				offset = screenOffset.offset;
			}
			renderPosition.position = screenPosition.position + offset;
		}
	}
}