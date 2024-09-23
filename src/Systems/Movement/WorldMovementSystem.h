#pragma once

#include <entt/entity/registry.hpp>

#include "Components/WorldMovementIntent.h"
#include "Systems/System.h"

namespace Sample::Systems::Movement {
	class WorldMovementSystem final : public System {
	public:
		explicit WorldMovementSystem(entt::registry& registry);

		void Update() override;

		void ApplyMovement(entt::entity entity, const Components::WorldMovementIntent& intent) const;

	private:
		entt::registry& _registry;
	};
}