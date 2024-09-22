#include "WorldMovementSystem.h"

#include "Components/WorldPosition.h"
#include "Components/WorldMovement.h"
#include "Components/ActionFinish.h"

namespace Sample::Systems::Movement {
	WorldMovementSystem::WorldMovementSystem(entt::registry &registry) : _registry(registry) {}

	void WorldMovementSystem::Update() {
		const auto& view = _registry.view<Components::WorldPosition, Components::WorldMovement, Components::ActionFinish>();
		for (auto [entity, position, movement] : view.each()) {
			position.x += movement.x;
			position.y += movement.y;
			_registry.remove<Components::WorldMovement>(entity);
		}
	}
}