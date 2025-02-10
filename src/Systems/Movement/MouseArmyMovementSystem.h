#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Movement {
	class MouseArmyMovementSystem final : public System {
	public:
		explicit MouseArmyMovementSystem(entt::registry &registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}