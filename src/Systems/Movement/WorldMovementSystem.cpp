#include "WorldMovementSystem.h"

#include "Components/WorldPosition.h"
#include "Events/WorldMovement.h"

namespace Sample::Systems::Movement {
	WorldMovementSystem::WorldMovementSystem(entt::registry &registry) : _registry(registry) {}

	void WorldMovementSystem::Update() {
		const auto& view = _registry.view<Components::WorldPosition, Events::WorldMovement>();
		for (const auto entity : view) {
			auto& position = view.get<Components::WorldPosition>(entity);
			const auto& movement = view.get<Events::WorldMovement>(entity);

			position.x += movement.x;
			position.y += movement.y;
		}
	}
}