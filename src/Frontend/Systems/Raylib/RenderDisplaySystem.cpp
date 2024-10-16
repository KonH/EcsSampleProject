#ifdef USE_RENDER_RAYLIB
#include "RenderDisplaySystem.h"

#include <raylib.h>

namespace Sample::Systems::Raylib {
	RenderDisplaySystem::RenderDisplaySystem(entt::registry&) {}

	void RenderDisplaySystem::Update() {
		EndDrawing();
	}
}
#endif