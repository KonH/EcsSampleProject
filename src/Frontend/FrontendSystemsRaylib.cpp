#ifdef USE_RENDER_RAYLIB
#include "FrontendSystems.h"

#include "Systems/Raylib/AppWindowInitSystem.h"
#include "Systems/Raylib/InputSystem.h"
#include "Systems/Raylib/RenderClearSystem.h"
#include "Systems/Raylib/RenderColorSystem.h"
#include "Systems/Raylib/RenderTextureSystem.h"
#include "Systems/Raylib/RenderLineSystem.h"
#include "Systems/Raylib/RenderTextSystem.h"
#include "Systems/Raylib/RenderDisplaySystem.h"

namespace Sample::Frontend {
	void FrontendSystems::PreMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		Add<Systems::Raylib::AppWindowInitSystem>(registry, systems);
		// All systems below depend on AppWindowInitSystem
		Add<Systems::Raylib::InputSystem>(registry, systems);
	}

	void FrontendSystems::PostMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		Add<Systems::Raylib::RenderClearSystem>(registry, systems);
		Add<Systems::Raylib::RenderColorSystem>(registry, systems);
		Add<Systems::Raylib::RenderTextureSystem>(registry, systems);
		Add<Systems::Raylib::RenderLineSystem>(registry, systems);
		Add<Systems::Raylib::RenderTextSystem>(registry, systems);
		Add<Systems::Raylib::RenderDisplaySystem>(registry, systems);
	}
}
#endif