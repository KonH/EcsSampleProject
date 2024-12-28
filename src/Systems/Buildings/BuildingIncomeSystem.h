#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Buildings {
	class BuildingIncomeSystem final : public System {
	public:
		explicit BuildingIncomeSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
