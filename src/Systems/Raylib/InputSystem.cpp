#include <Logging/Logger.h>
#ifdef USE_RENDER_RAYLIB
#include "InputSystem.h"

#include <raylib.h>

#include "Components/Runtime.h"
#include "Events/ControlPress.h"

namespace Sample::Systems::Raylib {
	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {}

	void InputSystem::Update() {
#if defined(PLATFORM_DESKTOP)
		if (WindowShouldClose()) {
			_registry.ctx().get<Components::Runtime>().isRunning = false;
		}
#endif
		for (int key = KEY_SPACE; key <= KEY_KB_MENU; ++key) {
			if (IsKeyPressed(key)) {
				OnKeyPressed(key);
			}
		}
	}

	void InputSystem::OnKeyPressed(int key) {
		Logging::Logger::LogInfo("Key pressed: " + std::to_string(key));
		// TODO
	}
}
#endif