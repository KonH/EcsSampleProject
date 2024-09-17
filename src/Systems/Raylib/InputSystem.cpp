#ifdef USE_RENDER_RAYLIB
#include "InputSystem.h"

#include <raylib.h>

#include "Components/Runtime.h"

namespace Sample::Systems::Raylib {
	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {}

	void InputSystem::Update() {
		if (WindowShouldClose()) {
			_registry.ctx().get<Components::Runtime>().isRunning = false;
		}
	}
}
#endif