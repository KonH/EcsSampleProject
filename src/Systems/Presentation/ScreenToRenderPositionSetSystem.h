#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class ScreenToRenderPositionSetSystem final : public System {
	public:
		explicit ScreenToRenderPositionSetSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}