#include "WorldToScreenPositionSystem.h"

#include "Components/RenderSettings.h"
#include "Components/WorldPosition.h"
#include "Components/ScreenPosition.h"
#include "Utils/VectorUtils.h"

namespace Sample::Systems::Presentation {
	WorldToScreenPositionSystem::WorldToScreenPositionSystem(entt::registry &registry) : _registry(registry) {}

	void WorldToScreenPositionSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto center = VectorUtils::GetScreenCenter(renderSettings);
		const auto& view = _registry.view<Components::WorldPosition, Components::ScreenPosition>();
		for (const auto entity : view) {
			const auto& worldPosition = view.get<Components::WorldPosition>(entity);
			auto& screenPosition = view.get<Components::ScreenPosition>(entity);
			screenPosition.position = VectorUtils::ToScreenPosition(renderSettings, center, worldPosition.position);
		}
	}
}