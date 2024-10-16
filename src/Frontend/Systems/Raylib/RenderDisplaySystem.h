#pragma once
#ifdef USE_RENDER_RAYLIB
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class RenderDisplaySystem final : public System {
	public:
		explicit RenderDisplaySystem(entt::registry& registry);

		void Update() override;
	};
}
#endif