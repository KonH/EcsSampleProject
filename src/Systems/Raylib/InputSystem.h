#pragma once
#ifdef USE_RENDER_RAYLIB
#include <entt/entity/registry.hpp>

#include "Systems/System.h"
#include "Types/ControlType.h"

namespace Sample::Systems::Raylib {
	class InputSystem final : public System {
	public:
		explicit InputSystem(entt::registry& registry);

		void Update() override;

	private:
		void OnKeyPress(int key) const;
		void OnKeyDown(int key) const;

		void RaiseControlPress(Types::ControlType key) const;
		void RaiseControlDown(Types::ControlType key) const;

	private:
		entt::registry& _registry;
	};
}
#endif