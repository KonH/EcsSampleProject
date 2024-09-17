#ifdef USE_RENDER_SFML
#include "FrontendSystems.h"

#include "Systems/SFML/AppWindowInitSystem.h"
#include "Systems/SFML/InputSystem.h"
#include "Systems/SFML/RenderClearSystem.h"
#include "Systems/SFML/RenderColorSystem.h"
#include "Systems/SFML/RenderTextSystem.h"
#include "Systems/SFML/RenderDisplaySystem.h"

namespace Sample::Frontend {
	void FrontendSystems::Initialize(entt::registry& registry, std::vector<std::unique_ptr<Sample::Systems::System>>& systems) {
		systems.emplace_back(std::make_unique<Systems::SFML::AppWindowInitSystem>(registry));
		// All systems below depend on AppWindowInitSystem
	    systems.emplace_back(std::make_unique<Systems::SFML::InputSystem>(registry));
	    systems.emplace_back(std::make_unique<Systems::SFML::RenderClearSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::SFML::RenderColorSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::SFML::RenderTextSystem>(registry));
		systems.emplace_back(std::make_unique<Systems::SFML::RenderDisplaySystem>(registry));
	}
}
#endif