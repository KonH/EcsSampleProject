#include "TurnAdvanceSystem.h"

#include "Common/ResourceConstants.h"
#include "Components/Click.h"
#include "Components/NextTurnButton.h"
#include "Components/ResourceHolder.h"
#include "Logging/Logger.h"

namespace Sample::Systems::Core {
	using namespace Sample::Components;

	TurnAdvanceSystem::TurnAdvanceSystem(entt::registry &registry) : _registry(registry) {}

	void TurnAdvanceSystem::Update() {
		auto clickView = _registry.view<Click, NextTurnButton>();
		auto resourceHolderView = _registry.view<ResourceHolder>();
		for (auto _: clickView) {
			for (auto&& [resourceEntity, resourceHolder]: resourceHolderView.each()) {
				auto it = resourceHolder.resources.find(Sample::ResourceConstants::TURNS_RESOURCE_ID);
				if (it != resourceHolder.resources.end()) {
					it->second += 1 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT;
					Sample::Logging::Logger::LogInfo("[TurnAdvanceSystem] Turn advanced to: {}", it->second);
				}
			}
		}
	}
}