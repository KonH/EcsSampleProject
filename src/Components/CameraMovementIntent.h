#pragma once

#include "Types/Vector2Float.h"

namespace Sample::Components {
	struct CameraMovementIntent {
		Types::Vector2Float wantedChange;
	};
}