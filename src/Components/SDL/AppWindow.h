#pragma once
#ifdef USE_RENDER_SDL
#include <SDL.h>

namespace Sample::Components::SDL {
	struct AppWindow {
		SDL_Window* window;
		SDL_Renderer* renderer;
	};
}
#endif