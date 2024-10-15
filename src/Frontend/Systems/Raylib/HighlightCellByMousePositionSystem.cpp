#include "HighlightCellByMousePositionSystem.h"

#include <raylib.h>

#include "Components/RenderSettings.h"
#include "Components/WorldPosition.h"
#include "Components/IsHighlightCell.h"
#include "Types/Vector2Float.h"
#include "Utils/VectorUtils.h"

namespace Sample::Systems::Raylib {
	HighlightCellByMousePositionSystem::HighlightCellByMousePositionSystem(entt::registry &registry) : _registry(registry) {}

	void HighlightCellByMousePositionSystem::Update() {
		const auto rawMousePosition = GetMousePosition();
		const auto mousePosition = Types::Vector2Float { rawMousePosition.x, rawMousePosition.y };

		const auto renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto center = VectorUtils::GetScreenCenter(renderSettings);

		const auto worldPosition = VectorUtils::ToWorldPosition(renderSettings, center, mousePosition);
		const auto worldPositionFloor = Types::Vector2Float { std::floor(worldPosition.x), std::floor(worldPosition.y) };
		const auto& view = _registry.view<Components::WorldPosition, Components::IsHighlightCell>();
		for (auto [_, position] : view.each()) {
			position.position = worldPositionFloor;
		}
	}
}