#pragma once

#include <entt/entt.hpp>

namespace Sample::Components {
	struct HasOwner {
		entt::entity owner;
	};
}
