#ifdef USE_RENDER_RAYLIB
#include "RenderClearSystem.h"

#include <raylib.h>

namespace Sample::Systems::Raylib {
	RenderClearSystem::RenderClearSystem(entt::registry &registry) : _registry(registry) {}

	void RenderClearSystem::Update() {
		BeginDrawing();
		ClearBackground(RAYWHITE);
	}
}
#endif