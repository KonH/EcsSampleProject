#include "PlayerMovementSystem.h"

#include "Components/IsPlayer.h"
#include "Components/WorldPosition.h"
#include "Events/ControlPress.h"
#include "Events/WorldMovement.h"

namespace Sample::Systems::Movement {
	PlayerMovementSystem::PlayerMovementSystem(entt::registry &registry) : _registry(registry) {}

	void PlayerMovementSystem::Update() {
		const auto& controlView = _registry.view<Events::ControlPress>();
		const auto& playerView = _registry.view<Components::IsPlayer, Components::WorldPosition>();
		for (const auto controlEntity : controlView) {
			const auto& control = controlView.get<Events::ControlPress>(controlEntity);
			for (const auto playerEntity : playerView) {
				switch (control.control) {
					case Types::ControlType::Right:
						_registry.emplace<Events::WorldMovement>(playerEntity, 1, 0);
						break;

					case Types::ControlType::Left:
						_registry.emplace<Events::WorldMovement>(playerEntity, -1, 0);
						break;

					case Types::ControlType::Down:
						_registry.emplace<Events::WorldMovement>(playerEntity, 0, 1);
						break;

					case Types::ControlType::Up:
						_registry.emplace<Events::WorldMovement>(playerEntity, 0, -1);
						break;

					default:
						// Not related
						break;
				}
			}
		}
	}
}