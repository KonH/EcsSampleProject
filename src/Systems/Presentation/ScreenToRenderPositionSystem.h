#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class ScreenToRenderPositionSystem final : public System {
	public:
		explicit ScreenToRenderPositionSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}