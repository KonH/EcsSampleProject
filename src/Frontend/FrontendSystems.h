#pragma once

#include <vector>
#include <memory>

#include <entt/entt.hpp>

#include "Systems/System.h"

namespace Sample::Frontend {
	class FrontendSystems {
	public:
		static void PreMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);
		static void PostMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);
	};
}