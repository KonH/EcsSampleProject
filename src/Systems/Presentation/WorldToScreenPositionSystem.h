#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class WorldToScreenPositionSystem final : public System {
	public:
		explicit WorldToScreenPositionSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}