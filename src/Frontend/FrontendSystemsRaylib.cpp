#ifdef USE_RENDER_RAYLIB
#include "FrontendSystems.h"

#include "Systems/Raylib/AppWindowInitSystem.h"
#include "Systems/Raylib/InputSystem.h"
#include "Systems/Raylib/RenderClearSystem.h"
#include "Systems/Raylib/RenderColorSystem.h"
#include "Systems/Raylib/RenderTextSystem.h"
#include "Systems/Raylib/RenderDisplaySystem.h"

namespace Sample::Frontend {
	void FrontendSystems::Initialize(entt::registry& registry, std::vector<std::unique_ptr<Sample::Systems::System>>& systems) {
		systems.emplace_back(std::make_unique<Systems::Raylib::AppWindowInitSystem>(registry));
		// All systems below depend on AppWindowInitSystem
		systems.emplace_back(std::make_unique<Systems::Raylib::InputSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::Raylib::RenderClearSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::Raylib::RenderColorSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::Raylib::RenderTextSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::Raylib::RenderDisplaySystem>(registry));
	}
}
#endif