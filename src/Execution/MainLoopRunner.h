#pragma once

#include <entt/entt.hpp>
#include <vector>
#include <memory>
#include "Systems/System.h"

namespace Sample::Execution {
	class MainLoopRunner {
	public:
		MainLoopRunner(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);
		void Run();

	private:
		entt::registry& _registry;
		std::vector<std::unique_ptr<Systems::System>>& _systems;
	};
}