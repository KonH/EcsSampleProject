#include "ResourceCounterUpdateSystem.h"

#include <cassert>

#include "Components/ResourceCounter.h"
#include "Components/ResourceHolder.h"
#include "Components/Text.h"

namespace Sample::Systems::Presentation {
	using namespace Sample::Components;

	ResourceCounterUpdateSystem::ResourceCounterUpdateSystem(entt::registry &registry) : _registry(registry) {}

	void ResourceCounterUpdateSystem::Update() {
		auto view = _registry.view<ResourceCounter, Text>();
		for (auto&& [entity, resourceCounter, text]: view.each()) {
			assert(_registry.valid(resourceCounter.resourceOwner) && "Resource owner entity is invalid");
			assert(_registry.all_of<ResourceHolder>(resourceCounter.resourceOwner) && "Resource owner entity does not have ResourceHolder component");
			const auto& resourceHolder = _registry.get<ResourceHolder>(resourceCounter.resourceOwner);
			
			auto it = resourceHolder.resources.find(resourceCounter.resourceId);
			assert(it != resourceHolder.resources.end() && "Resource ID is invalid");

			auto resourceAmount = it->second;

			// TODO: do not update text if the value is the same
			text.text = resourceCounter.resourceId + ": " + std::to_string(resourceAmount);
		}
	}
}
