#pragma once

#include <map>
#include <string>

#include <entt/entt.hpp>

namespace Sample::Components {
	struct ResourceHolder {
		// Represent resource 0.01 fraction per unit (1 unit to display - 100 units in storage by default)
		// Specific value is presented in Constants::RESOURCE_UNITS_PER_DISPLAY_UNIT at Common/ResourceConstants.h
		std::map<std::string, long> resources;
	};
}
