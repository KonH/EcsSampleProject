#ifdef USE_RENDER_SDL
#include "FrontendSystems.h"

#include "Systems/SDL/AppWindowInitSystem.h"
#include "Systems/SDL/InputSystem.h"
#include "Systems/SDL/RenderClearSystem.h"
#include "Systems/SDL/RenderColorSystem.h"
#include "Systems/SDL/RenderDisplaySystem.h"

namespace Sample::Frontend {
	void FrontendSystems::Initialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		systems.emplace_back(std::make_unique<Systems::SDL::AppWindowInitSystem>(registry));
		// All systems below are dependent on AppWindowInitSystem
	    systems.emplace_back(std::make_unique<Systems::SDL::InputSystem>(registry));
	    systems.emplace_back(std::make_unique<Systems::SDL::RenderClearSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::SDL::RenderColorSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::SDL::RenderDisplaySystem>(registry));
	}
}
#endif