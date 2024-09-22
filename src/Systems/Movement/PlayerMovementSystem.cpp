#include "PlayerMovementSystem.h"

#include "Components/IsPlayer.h"
#include "Components/WorldPosition.h"
#include "Components/ControlPress.h"
#include "Components/WorldMovement.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"

namespace Sample::Systems::Movement {
	PlayerMovementSystem::PlayerMovementSystem(entt::registry &registry) : _registry(registry) {}

	void PlayerMovementSystem::Update() {
		const auto&	controlView = _registry.view<Components::ControlPress>();
		const auto& playerView = _registry.view<Components::IsPlayer, Components::WorldPosition>(entt::exclude<Components::ActionProgress>);
		for (auto [controlEntity, control] : controlView.each()) {
			for (auto [playerEntity, _] : playerView.each()) {
				switch (control.control) {
					case Types::ControlType::Right:
						ApplyMovement(playerEntity, 1, 0);
						break;

					case Types::ControlType::Left:
						ApplyMovement(playerEntity, -1, 0);
						break;

					case Types::ControlType::Down:
						ApplyMovement(playerEntity, 0, 1);
						break;

					case Types::ControlType::Up:
						ApplyMovement(playerEntity, 0, -1);
						break;

					default:
						// Not related
						break;
				}
			}
		}
	}

	void PlayerMovementSystem::ApplyMovement(const entt::entity entity, const int x, const int y) const {
		_registry.emplace<Components::WorldMovement>(entity, x, y);
		_registry.emplace<Components::ActionProgress>(entity, 0.0f, 0.15f); // TODO: make duration configurable
		_registry.emplace<Components::ActionStart>(entity);
	}
}