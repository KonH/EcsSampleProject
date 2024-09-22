#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Movement {
	class PlayerMovementSystem final : public System {
	public:
		explicit PlayerMovementSystem(entt::registry& registry);

		void Update() override;

		void ApplyMovement(entt::entity entity, int x, int y) const;

	private:
		entt::registry& _registry;
	};
}