#pragma once

#include <string>

namespace Sample::Components {
	struct RenderSettings {
		std::string windowTitle;
		unsigned int screenWidth;
		unsigned int screenHeight;
		float unitSize;
	};
}
