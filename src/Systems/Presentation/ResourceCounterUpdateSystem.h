#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class ResourceCounterUpdateSystem final : public System {
	public:
		explicit ResourceCounterUpdateSystem(entt::registry &registry);

		void Update() override;

	private:
		entt::registry &_registry;
	};
}
