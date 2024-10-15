#pragma once

#include <string>

#include <Types/Vector2Float.h>

namespace Sample::Components {
	struct RenderSettings {
		std::string windowTitle;
		unsigned int screenWidth;
		unsigned int screenHeight;
		float unitSize;
		Types::Vector2Float cameraCenter;
	};
}
