#include "CameraMovementIntentSystem.h"

#include "Components/MouseMove.h"
#include "Components/ControlDown.h"
#include "Components/CameraMovementIntent.h"

namespace Sample::Systems::Camera {
	CameraMovementIntentSystem::CameraMovementIntentSystem(entt::registry &registry) : _registry(registry) {}

	void CameraMovementIntentSystem::Update() {
		const auto&	controlView = _registry.view<Components::ControlDown>();
		const auto&	mouseMoveView = _registry.view<Components::MouseMove>();
		for (auto [_, mouseMove] : mouseMoveView.each()) {
			for (auto [_, control] : controlView.each()) {
				if (control.control != Types::ControlType::LeftMouseButton) {
					continue;
				}
				_registry.emplace<Components::CameraMovementIntent>(_registry.create(), mouseMove.change.x, mouseMove.change.y);
			}
		}
	}
}