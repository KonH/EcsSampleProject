#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Movement {
	class ObstacleFilterSystem final : public System {
	public:
		explicit ObstacleFilterSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}