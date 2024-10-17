#pragma once

#include <vector>
#include "Types/Vector2Float.h"

namespace Sample::Components {
	struct WorldPositionSet {
		std::vector<Types::Vector2Float> positions;
	};
}