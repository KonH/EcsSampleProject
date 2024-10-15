#include "PlayerMovementSystem.h"

#include "Components/ActionProgress.h"
#include "Components/ControlDown.h"
#include "Components/IsPlayer.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

namespace Sample::Systems::Movement {
	PlayerMovementSystem::PlayerMovementSystem(entt::registry &registry) : _registry(registry) {}

	void PlayerMovementSystem::Update() {
		const auto&	controlView = _registry.view<Components::ControlDown>();
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
		_registry.emplace<Components::WorldMovementIntent>(entity, static_cast<float>(x), static_cast<float>(y));
	}
}