#pragma once

#include <string>
#include <limits>

#include <entt/entt.hpp>

namespace Sample::Components {
	struct ResourceCounter {
		std::string resourceId;
		entt::entity resourceOwner;

		double lastAmount = std::numeric_limits<double>::quiet_NaN();
	};
}
