#pragma once

#include "Types/Vector2Int.h"

namespace Sample::Components {
	struct WorldMovementIntent {
		Types::Vector2Int wantedChange;
	};
}