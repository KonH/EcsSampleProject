#include "CameraZoomSystem.h"

#include "Components/RenderSettings.h"
#include "Components/MouseScroll.h"

namespace Sample::Systems::Camera {
	CameraZoomSystem::CameraZoomSystem(entt::registry &registry) : _registry(registry) {}

	void CameraZoomSystem::Update() {
		// TODO: make configurable
		constexpr float zoomFactor = 1.1f;

		auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();

		const auto view = _registry.view<Components::MouseScroll>();
		for (auto [_, mouseScroll] : view.each()) {
			renderSettings.unitSize *= std::pow(zoomFactor, std::copysign(1.0f, mouseScroll.scrollChange));
		}
	}
}