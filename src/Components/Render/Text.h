#pragma once

#include <string>

#include "Types/Color.h"

namespace Sample::Components::Render {
	struct Text {
		std::string fontName;
		float size;
		std::string text;
	};
}