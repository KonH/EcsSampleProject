#pragma once
#ifdef USE_RENDER_RAYLIB
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class InputSystem final : public System {
	public:
		explicit InputSystem(entt::registry& registry);

		void Update() override;

	private:
		void OnKeyPressed(int key);

	private:
		entt::registry& _registry;
	};
}
#endif