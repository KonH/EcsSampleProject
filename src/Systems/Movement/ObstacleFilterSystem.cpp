#include "ObstacleFilterSystem.h"

#include "Components/ActionProgress.h"
#include "Components/ControlPress.h"
#include "Components/IsObstacle.h"
#include "Components/IsPlayer.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

namespace Sample::Systems::Movement {
	ObstacleFilterSystem::ObstacleFilterSystem(entt::registry &registry) : _registry(registry) {}

	void ObstacleFilterSystem::Update() {
		const auto& movementIntentView = _registry.view<Components::WorldPosition, Components::WorldMovementIntent>();
		const auto& obstaclePositionView = _registry.view<Components::WorldPosition, Components::IsObstacle>();
		// TODO: optimize this
		for (auto [intentEntity, movablePosition, intent] : movementIntentView.each()) {
			const auto desiredPosition = movablePosition.position + intent.wantedChange;
			for (auto [positionEntity, obstaclePosition] : obstaclePositionView.each()) {
				if (desiredPosition == obstaclePosition.position) {
					_registry.remove<Components::WorldMovementIntent>(intentEntity);
				}
			}
		}
	}
}