#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Animation {
	class MovementAnimationSystem final : public System {
	public:
		explicit MovementAnimationSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}