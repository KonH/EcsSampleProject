#include "WorldToScreenPositionSystem.h"

#include "Components/RenderSettings.h"
#include "Components/WorldPosition.h"
#include "Components/ScreenPosition.h"

namespace Sample::Systems::Presentation {
	WorldToScreenPositionSystem::WorldToScreenPositionSystem(entt::registry &registry) : _registry(registry) {}

	void WorldToScreenPositionSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto unitSize = renderSettings.unitSize;
		const auto centerX = static_cast<float>(renderSettings.screenWidth) / 2.f - unitSize / 2.f;
		const auto centerY = static_cast<float>(renderSettings.screenHeight) / 2.f - unitSize / 2.f;
		const auto& view = _registry.view<Components::WorldPosition, Components::ScreenPosition>();
		for (const auto entity : view) {
			const auto& worldPosition = view.get<Components::WorldPosition>(entity);
			auto& screenPosition = view.get<Components::ScreenPosition>(entity);
			screenPosition.position.x = static_cast<int>(centerX + static_cast<float>(worldPosition.position.x) * unitSize);
			screenPosition.position.y = static_cast<int>(centerY + static_cast<float>(worldPosition.position.y) * unitSize);
		}
	}
}