#pragma once

#include <entt/entt.hpp>

#include "System.h"

namespace Sample::Systems {
	class SystemsBuilder {
	public:
		static void PreMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);
		static void MainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);
		static void PostMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems);

	private:
		template<typename T>
		static void Add(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
			systems.push_back(std::make_unique<T>(registry));
		};
	};
}

