#include "WorldToScreenPositionSetSystem.h"

#include "Components/RenderSettings.h"
#include "Components/WorldPositionSet.h"
#include "Components/ScreenPositionSet.h"
#include "Utils/VectorUtils.h"

namespace Sample::Systems::Presentation {
	WorldToScreenPositionSetSystem::WorldToScreenPositionSetSystem(entt::registry &registry) : _registry(registry) {}

	void WorldToScreenPositionSetSystem::Update() {
		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto center = VectorUtils::GetScreenCenter(renderSettings);
		const auto& view = _registry.view<Components::WorldPositionSet, Components::ScreenPositionSet>();
		for (auto [entity, worldPosition, screenPosition] : view.each()) {
			auto& worldPositions = worldPosition.positions;
			auto& screenPositions = screenPosition.positions;
			if (screenPositions.size() != worldPositions.size()) {
				screenPositions.clear();
				screenPositions.resize(worldPositions.size());
			}
			for (auto i = 0; i < worldPositions.size(); ++i) {
				screenPositions[i] = VectorUtils::ToScreenPosition(renderSettings, center,worldPositions[i]);
			}
		}
	}
}