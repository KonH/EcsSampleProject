#pragma once

#include <string>

#include "Types/Color.h"

namespace Sample::Components {
	struct Text {
		std::string fontName;
		int size;
		std::string text;
	};
}