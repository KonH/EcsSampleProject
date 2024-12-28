#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Core {
	class TurnAdvanceSystem final : public System {
	public:
		explicit TurnAdvanceSystem(entt::registry &registry);

		void Update() override;

	private:
		entt::registry &_registry;
	};
}
