#include "CameraMovementSystem.h"

#include "Components/RenderSettings.h"
#include "Components/CameraMovementIntent.h"

namespace Sample::Systems::Camera {
	CameraMovementSystem::CameraMovementSystem(entt::registry &registry) : _registry(registry) {}

	void CameraMovementSystem::Update() {
		// TODO: limits in separated filter system
		auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto&	intentView = _registry.view<Components::CameraMovementIntent>();
		for (auto [_, intent] : intentView.each()) {
			renderSettings.cameraCenter += intent.wantedChange;
		}
	}
}