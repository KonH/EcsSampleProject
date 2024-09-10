#pragma once

#include <entt/entity/registry.hpp>

#include "System.h"

namespace Sample::Systems {
	class RenderSystem final : public System {
	public:
		explicit RenderSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
