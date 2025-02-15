#pragma once

#include <entt/entity/registry.hpp>
#include "Systems/System.h"

namespace Sample::Systems::Animation {
	class TextBounceAnimationSystem final : public System {
	public:
		explicit TextBounceAnimationSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
