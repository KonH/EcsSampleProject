#include "ResourceCounterUpdateSystem.h"

#include <iomanip>
#include <sstream>

#include "Common/ResourceConstants.h"

#include "Logging/Logger.h"

#include "Components/ResourceCounter.h"
#include "Components/ResourceHolder.h"
#include "Components/Text.h"

namespace Sample::Systems::Presentation {
	using namespace Sample::Components;

	ResourceCounterUpdateSystem::ResourceCounterUpdateSystem(entt::registry &registry) : _registry(registry) {}

	void ResourceCounterUpdateSystem::Update() {
		auto view = _registry.view<ResourceCounter, Text>();
		for (auto&& [entity, resourceCounter, text]: view.each()) {
			if (!_registry.valid(resourceCounter.resourceOwner)) {
				// TODO: simplify entity ID logging
				Sample::Logging::Logger::LogError("[ResourceCounterUpdateSystem] Resource owner entity is invalid: {}", std::to_string(static_cast<int>(resourceCounter.resourceOwner)));
				continue;
			}
			if (const auto &resourceHolder = _registry.try_get<ResourceHolder>(resourceCounter.resourceOwner)) {
				auto it = resourceHolder->resources.find(resourceCounter.resourceId);
				if (it == resourceHolder->resources.end()) {
					Sample::Logging::Logger::LogError(
						"[ResourceCounterUpdateSystem] Resource owner entity does not have resource: {}",
						resourceCounter.resourceId);
					continue;
				}

				auto resourceAmount = it->second;

				double displayAmount = static_cast<double>(resourceAmount) / ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT;

				std::ostringstream oss;
				oss << std::fixed << std::setprecision(3) << displayAmount;

				// Remove trailing zeros and the decimal point if not needed
				std::string displayAmountStr = oss.str();
				displayAmountStr.erase(displayAmountStr.find_last_not_of('0') + 1, std::string::npos);
				if (displayAmountStr.back() == '.') {
					displayAmountStr.pop_back();
				}

				// TODO: do not update text if the value is the same
				text.text = resourceCounter.resourceId + ": " + displayAmountStr;
			} else {
				Sample::Logging::Logger::LogError(
					"[ResourceCounterUpdateSystem] Resource owner entity does not have ResourceHolder component: {}",
					std::to_string(static_cast<int>(resourceCounter.resourceOwner)));
			}
		}
	}
}
