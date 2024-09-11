#pragma once
#ifdef USE_RENDER_SFML
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::SFML {
	class RenderSystem final : public System {
	public:
		explicit RenderSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
#endif