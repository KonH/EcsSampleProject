#pragma once
#ifdef USE_RENDER_SDL
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::SDL {
	class InputSystem final : public System {
	public:
		explicit InputSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
#endif