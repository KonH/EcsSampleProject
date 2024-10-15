#pragma once

#include "Types/Vector2Float.h"

namespace Sample::Components {
	struct WorldMovementIntent {
		Types::Vector2Float wantedChange;
	};
}