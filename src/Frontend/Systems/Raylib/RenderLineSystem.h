#pragma once
#ifdef USE_RENDER_RAYLIB
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class RenderLineSystem final : public System {
	public:
		explicit RenderLineSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
#endif