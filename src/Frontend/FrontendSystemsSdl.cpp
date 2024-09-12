#ifdef USE_RENDER_SDL
#include "FrontendSystems.h"

#include "Systems/SDL/AppWindowInitSystem.h"
#include "Systems/SDL/InputSystem.h"
#include "Systems/SDL/RenderSystem.h"

namespace Sample::Frontend {
	void FrontendSystems::Initialize(entt::registry& registry, std::vector<std::unique_ptr<Sample::Systems::System>>& systems) {
		systems.emplace_back(std::make_unique<Systems::SDL::AppWindowInitSystem>(registry));
	    systems.emplace_back(std::make_unique<Systems::SDL::InputSystem>(registry)); // InputSystem depends on AppWindowInitSystem
	    systems.emplace_back(std::make_unique<Systems::SDL::RenderSystem>(registry)); // RenderSystem depends on AppWindowInitSystem
	}
}
#endif