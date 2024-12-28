#ifdef USE_RENDER_RAYLIB
#include "InputSystem.h"

#include <raylib.h>

#include "Components/Runtime.h"
#include "Components/ControlPress.h"
#include "Components/ControlDown.h"
#include "Components/MouseScroll.h"
#include "Components/MousePosition.h"
#include "Components/MouseMove.h"

#include "Logging/Logger.h"

namespace Sample::Systems::Raylib {
	using namespace Logging;

	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {
		_registry.ctx().emplace<Components::MousePosition>();
	}

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
			if (IsKeyDown(key)) {
				OnKeyDown(key);
			}
		}
		
		const auto mouseWheelMove = GetMouseWheelMove();
		if (std::abs(mouseWheelMove) > 0.01f) {
			_registry.emplace<Components::MouseScroll>(_registry.create(), mouseWheelMove);
		}
		
		const auto rawMousePosition = GetMousePosition();
		const auto mousePosition = Types::Vector2Float { rawMousePosition.x, rawMousePosition.y };
		_registry.ctx().get<Components::MousePosition>().position = mousePosition;

		const auto mouseDelta = GetMouseDelta();
		if ((std::abs(mouseDelta.x) > 0.01f) || (std::abs(mouseDelta.y) > 0.01f)) {
			const Types::Vector2Float mouseDeltaVec = { mouseDelta.x, mouseDelta.y };
			_registry.emplace<Components::MouseMove>(_registry.create(), mouseDeltaVec);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Logger::LogInfo("[InputSystem] Left mouse button click at {}x{}", mousePosition.x, mousePosition.y);
			RaiseControlPress(Types::ControlType::LeftMouseButton);
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			RaiseControlDown(Types::ControlType::LeftMouseButton);
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

	void InputSystem::OnKeyDown(const int key) const {
		switch (key) {
			case KEY_RIGHT:
				RaiseControlDown(Types::ControlType::Right);
			break;

			case KEY_LEFT:
				RaiseControlDown(Types::ControlType::Left);
			break;

			case KEY_DOWN:
				RaiseControlDown(Types::ControlType::Down);
			break;

			case KEY_UP:
				RaiseControlDown(Types::ControlType::Up);
			break;

			default:
				// Non-control key down
				break;
		}
	}

	void InputSystem::RaiseControlPress(const Types::ControlType key) const {
		_registry.emplace<Components::ControlPress>(_registry.create(), key);
	}

	void InputSystem::RaiseControlDown(const Types::ControlType key) const {
		_registry.emplace<Components::ControlDown>(_registry.create(), key);
	}
}
#endif