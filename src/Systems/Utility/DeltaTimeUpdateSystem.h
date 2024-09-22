#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Utility {
	class DeltaTimeUpdateSystem final : public System {
	public:
		explicit DeltaTimeUpdateSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
		long long _lastUpdateTime;
	};
}