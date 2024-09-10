#pragma once

#include <entt/entity/registry.hpp>

#include "System.h"

namespace Sample::Systems {
	class InputSystem final : public System {
	public:
		explicit InputSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
