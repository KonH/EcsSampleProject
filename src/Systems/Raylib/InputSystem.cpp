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
				OnKeyPress(key);
			}
		}
	}

	void InputSystem::OnKeyPress(const int key) const {
		switch (key) {
			case KEY_RIGHT:
				RaiseControlPress(Types::ControlType::Right);
				break;

			case KEY_LEFT:
				RaiseControlPress(Types::ControlType::Left);
				break;

			case KEY_DOWN:
				RaiseControlPress(Types::ControlType::Down);
				break;

			case KEY_UP:
				RaiseControlPress(Types::ControlType::Up);
				break;

			default:
				// Non-control key down
				break;
		}
	}

	void InputSystem::RaiseControlPress(const Types::ControlType key) const {
		_registry.emplace<Events::ControlPress>(_registry.create(), key);
	}
}
#endif