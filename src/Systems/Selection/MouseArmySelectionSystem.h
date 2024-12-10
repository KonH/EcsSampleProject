#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Selection {
	class MouseArmySelectionSystem final : public System {
	public:
		explicit MouseArmySelectionSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}