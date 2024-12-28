#include "BuildingIncomeSystem.h"

#include "Logging/Logger.h"

#include "Configs/BuildingConfig.h"
#include "Configs/BuildingConfigProvider.h"

#include "Components/Building.h"
#include "Components/HasOwner.h"
#include "Components/Province.h"
#include "Components/ResourceHolder.h"
#include "Components/Turn.h"

namespace Sample::Systems::Buildings {
	using namespace Sample::Components;

	BuildingIncomeSystem::BuildingIncomeSystem(entt::registry& registry) : _registry(registry) {}

	void BuildingIncomeSystem::Update() {
		auto turnView = _registry.view<Turn>();
		if (turnView.empty()) {
			return;
		}

		auto& buildingConfigProvider = _registry.ctx().get<Sample::Configs::BuildingConfigProvider>();
		auto provinceView = _registry.view<Province, HasOwner>();
		for (auto&& [provinceEntity, hasOwner]: provinceView.each()) {
			auto playerEntity = hasOwner.owner;
			auto resourceHolder = _registry.try_get<ResourceHolder>(playerEntity);
			if (!resourceHolder) {
				continue;
			}

			auto buildingView = _registry.view<Building, HasOwner>();
			for (auto&& [buildingEntity, building, buildingOwner]: buildingView.each()) {
				if (buildingOwner.owner != provinceEntity) {
					continue;
				}

				auto buildingConfig = buildingConfigProvider.GetBuildingConfig(building.configId);
				if (!buildingConfig) {
					continue;
				}

				// TODO: replace with event
				for (const auto& [resourceId, income]: buildingConfig->income) {
					(*resourceHolder).resources[resourceId] += income;
					Sample::Logging::Logger::LogInfo(
						"[BuildingIncomeSystem] Added {} to {} for player {}", income,
						resourceId, static_cast<int>(playerEntity));
				}
			}
		}
	}
}
