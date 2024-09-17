#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Types/Color.h"

namespace Sample::Systems::SFML::Utils {
	inline sf::Color ConvertColor(const Types::Color& color) {
		return { color.red, color.green, color.blue, color.alpha };
	}
}