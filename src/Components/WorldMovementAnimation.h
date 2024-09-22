#pragma once

#include <tweeny.h>

namespace Sample::Components {
	struct WorldMovementAnimation {
		tweeny::tween<float, float> tween;
	};
}