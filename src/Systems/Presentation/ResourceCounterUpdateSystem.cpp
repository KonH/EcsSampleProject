#include "ResourceCounterUpdateSystem.h"

#include <iomanip>
#include <sstream>

#include "Common/ResourceConstants.h"

#include "Logging/Logger.h"

#include "Components/ResourceCounter.h"
#include "Components/ResourceHolder.h"

#include "Components/Render/Text.h"

#include "Components/Presentation/NeedBounceAnimation.h"

namespace Sample::Systems::Presentation {
	using namespace Sample::Components;
	using namespace Sample::Components::Render;
	using namespace Sample::Components::Presentation;

	ResourceCounterUpdateSystem::ResourceCounterUpdateSystem(entt::registry &registry) : _registry(registry) {}

	void ResourceCounterUpdateSystem::Update() {
		auto view = _registry.view<ResourceCounter, Text>();
		for (auto&& [entity, resourceCounter, text]: view.each()) {
			if (!_registry.valid(resourceCounter.resourceOwner)) {
				// TODO: simplify entity ID logging
				Sample::Logging::Logger::LogError("[ResourceCounterUpdateSystem] Resource owner entity is invalid: {}", std::to_string(static_cast<int>(resourceCounter.resourceOwner)));
				continue;
			}
			if (const auto& resourceHolder = _registry.try_get<ResourceHolder>(resourceCounter.resourceOwner)) {
				auto it = resourceHolder->resources.find(resourceCounter.resourceId);
				if (it == resourceHolder->resources.end()) {
					Sample::Logging::Logger::LogError(
						"[ResourceCounterUpdateSystem] Resource owner entity does not have resource: {}",
						resourceCounter.resourceId);
					continue;
				}

				auto resourceAmount = it->second;

				double displayAmount = ResourceConstants::GetDisplayUnits(resourceAmount);

				constexpr double epsilon = 1e-9;
				if (std::fabs(displayAmount - resourceCounter.lastAmount) < epsilon) {
					continue;
				}

				std::ostringstream oss;
				oss << std::fixed << std::setprecision(3) << displayAmount;

				// Remove trailing zeros and the decimal point if not needed
				std::string displayAmountStr = oss.str();
				displayAmountStr.erase(displayAmountStr.find_last_not_of('0') + 1, std::string::npos);
				if (displayAmountStr.back() == '.') {
					displayAmountStr.pop_back();
				}

				text.text = resourceCounter.resourceId + ": " + displayAmountStr;
				
				if (!std::isnan(resourceCounter.lastAmount)) {
					_registry.emplace<NeedBounceAnimation>(entity);
				}

				resourceCounter.lastAmount = displayAmount;
			} else {
				Sample::Logging::Logger::LogError(
					"[ResourceCounterUpdateSystem] Resource owner entity does not have ResourceHolder component: {}",
					std::to_string(static_cast<int>(resourceCounter.resourceOwner)));
			}
		}
	}
}
