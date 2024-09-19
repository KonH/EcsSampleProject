#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Movement {
	class WorldMovementSystem final : public System {
	public:
		explicit WorldMovementSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}