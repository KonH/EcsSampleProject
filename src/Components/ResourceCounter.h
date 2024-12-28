#pragma once

#include <string>

#include <entt/entt.hpp>

namespace Sample::Components {
	struct ResourceCounter {
		std::string resourceId;
		entt::entity resourceOwner;
	};
}
