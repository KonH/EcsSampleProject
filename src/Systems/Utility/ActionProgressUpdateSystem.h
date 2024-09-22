#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Utility {
	class ActionProgressUpdateSystem final : public System {
	public:
		explicit ActionProgressUpdateSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}