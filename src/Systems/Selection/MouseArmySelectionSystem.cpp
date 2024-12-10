#include "MouseArmySelectionSystem.h"

#include "Components/ControlPress.h"
#include "Components/RenderSettings.h"
#include "Components/MousePosition.h"
#include "Components/WorldPosition.h"
#include "Components/Army.h"
#include "Components/IsPlayer.h"
#include "Components/IsSelected.h"
#include "Utils/VectorUtils.h"
#include "Logging/Logger.h"

namespace Sample::Systems::Selection {
	MouseArmySelectionSystem::MouseArmySelectionSystem(entt::registry &registry) : _registry(registry) {}

	void MouseArmySelectionSystem::Update() {
		bool isClickFound = false;
		const auto& controlView = _registry.view<Components::ControlPress>();
		for (auto [entity, controlPress]: controlView.each()) {
			if (controlPress.control == Types::ControlType::LeftMouseButton) {
				isClickFound = true;
				break;
			}
		}
		if (!isClickFound) {
			return;
		}
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto& center = VectorUtils::GetScreenCenter(renderSettings);
		const auto& mousePosition = _registry.ctx().get<Components::MousePosition>();
		const auto& worldPosition = VectorUtils::ToWorldPosition(renderSettings, center, mousePosition.position);
		const auto& worldPositionFloor = Types::Vector2Float { std::floor(worldPosition.x), std::floor(worldPosition.y) };
		const auto& view = _registry.view<Components::WorldPosition, Components::Army, Components::IsPlayer>();
		for (auto [entity, position]: view.each()) {
			if (position.position == worldPositionFloor) {
				if (_registry.all_of<Components::IsSelected>(entity)) {
					Logging::Logger::LogInfo("[MouseArmySelectionSystem] Deselecting army");
					_registry.remove<Components::IsSelected>(entity);
				} else {
					Logging::Logger::LogInfo("[MouseArmySelectionSystem] Selecting army");
					_registry.emplace<Components::IsSelected>(entity);
				}
			}
		}
	}
}