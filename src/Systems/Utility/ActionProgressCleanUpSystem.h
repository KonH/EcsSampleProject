#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Utility {
	class ActionProgressCleanUpSystem final : public System {
	public:
		explicit ActionProgressCleanUpSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}