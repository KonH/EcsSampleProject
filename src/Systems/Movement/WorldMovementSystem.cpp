#include "WorldMovementSystem.h"

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"
#include "Components/WorldMovement.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

namespace Sample::Systems::Movement {
	WorldMovementSystem::WorldMovementSystem(entt::registry &registry) : _registry(registry) {}

	void WorldMovementSystem::Update() {
		const auto& initiateMovementView = _registry.view<Components::WorldMovementIntent>();
		for (auto [entity, intent] : initiateMovementView.each()) {
			ApplyMovement(entity, intent);
		}
		const auto& applyNewPositionView = _registry.view<Components::WorldPosition, Components::WorldMovement, Components::ActionFinish>();
		for (auto [entity, position, movement] : applyNewPositionView.each()) {
			position.position += movement.change;
			_registry.remove<Components::WorldMovement>(entity);
		}
	}

	void WorldMovementSystem::ApplyMovement(const entt::entity entity, const Components::WorldMovementIntent& intent) const {
		_registry.emplace<Components::WorldMovement>(entity, intent.wantedChange);
		_registry.emplace<Components::ActionProgress>(entity, 0.0f, 0.15f); // TODO: make duration configurable
		_registry.emplace<Components::ActionStart>(entity);
	}
}