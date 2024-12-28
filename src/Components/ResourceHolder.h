#pragma once

#include <map>
#include <string>

#include <entt/entt.hpp>

namespace Sample::Components {
	struct ResourceHolder {
		// Represent resource 0.001 fraction per unit (1 unit to display - 1000 units in storage)
		std::map<std::string, long> resources;
	};
}
