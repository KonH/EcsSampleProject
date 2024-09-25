#pragma once
#ifdef USE_RENDER_RAYLIB
#include <raylib.h>

#include "Types/Color.h"

namespace Sample::Systems::Raylib::Utils {
	inline Color ConvertColor(const Types::Color& color) {
		return { color.red, color.green, color.blue, color.alpha };
	}
}
#endif