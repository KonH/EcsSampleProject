#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Camera {
	class CameraMovementSystem final : public System {
	public:
		explicit CameraMovementSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}