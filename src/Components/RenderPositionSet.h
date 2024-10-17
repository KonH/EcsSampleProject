#pragma once

#include <vector>
#include "Types/Vector2Int.h"

namespace Sample::Components {
	struct RenderPositionSet {
		std::vector<Types::Vector2Int> positions;
	};
}