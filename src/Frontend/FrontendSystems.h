#pragma once

#include <vector>
#include <memory>

#include <entt/entt.hpp>

#include "Systems/System.h"

namespace Sample::Frontend {
	class FrontendSystems {
	public:
		static void Initialize(entt::registry& registry, std::vector<std::unique_ptr<Sample::Systems::System>>& systems);
	};
}