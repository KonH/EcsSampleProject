#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class WorldToScreenPositionSetSystem final : public System {
	public:
		explicit WorldToScreenPositionSetSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}