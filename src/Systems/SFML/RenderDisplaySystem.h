#pragma once
#ifdef USE_RENDER_SFML
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::SFML {
	class RenderDisplaySystem final : public System {
	public:
		explicit RenderDisplaySystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
#endif