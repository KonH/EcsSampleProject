#pragma once

#include <tweeny.h>

namespace Sample::Components::Animation {
	struct TextBounceAnimation {
		tweeny::tween<float> tween;
		float baseTextSize;
	};
}
