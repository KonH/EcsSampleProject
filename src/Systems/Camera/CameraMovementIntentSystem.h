#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Camera {
	class CameraMovementIntentSystem final : public System {
	public:
		explicit CameraMovementIntentSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}