#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Camera {
	class CameraZoomSystem final : public System {
	public:
		explicit CameraZoomSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}