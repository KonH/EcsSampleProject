#ifdef USE_RENDER_SFML
#include "FrontendSystems.h"

#include "Systems/SFML/AppWindowInitSystem.h"
#include "Systems/SFML/InputSystem.h"
#include "Systems/SFML/RenderSystem.h"

namespace Sample::Frontend {
	void FrontendSystems::Initialize(entt::registry& registry, std::vector<std::unique_ptr<Sample::Systems::System>>& systems) {
		systems.emplace_back(std::make_unique<Systems::SFML::AppWindowInitSystem>(registry));
	    systems.emplace_back(std::make_unique<Systems::SFML::InputSystem>(registry)); // InputSystem depends on AppWindowInitSystem
	    systems.emplace_back(std::make_unique<Systems::SFML::RenderSystem>(registry)); // RenderSystem depends on AppWindowInitSystem
	}
}
#endif