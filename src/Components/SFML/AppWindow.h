#pragma once
#ifdef USE_RENDER_SFML
#include <SFML/Graphics/RenderWindow.hpp>

namespace Sample::Components::SFML {
	struct AppWindow {
		sf::RenderWindow window;
	};
}
#endif