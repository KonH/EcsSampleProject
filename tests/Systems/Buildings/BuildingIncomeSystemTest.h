#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Common/ResourceConstants.h"
#include "Components/Building.h"
#include "Components/HasOwner.h"
#include "Components/Province.h"
#include "Components/ResourceHolder.h"
#include "Components/Turn.h"
#include "Configs/BuildingConfig.h"
#include "Configs/BuildingConfigProvider.h"
#include "Systems/Buildings/BuildingIncomeSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleBuildingIncomeSystemTest, IncomeIsAddedOnTurn) {
		entt::registry registry;

		// Set up building config
		auto &ctx = registry.ctx();
		std::map<std::string, Sample::Configs::BuildingConfig> buildingConfigs;
		buildingConfigs["TownHall"] = Sample::Configs::BuildingConfig{
				"TownHall", {{"Coins", Sample::ResourceConstants::GetResourceUnits(100)}}};
		ctx.emplace<Sample::Configs::BuildingConfigProvider>(buildingConfigs);

		// Create a player entity with ResourceHolder
		const auto playerEntity = registry.create();
		std::map<std::string, long> playerResources;
		playerResources["Coins"] = 0;
		registry.emplace<Sample::Components::ResourceHolder>(playerEntity, playerResources);

		// Create a province entity owned by the player
		const auto provinceEntity = registry.create();
		registry.emplace<Sample::Components::Province>(provinceEntity);
		registry.emplace<Sample::Components::HasOwner>(provinceEntity, playerEntity);

		// Create a building entity in the province
		const auto buildingEntity = registry.create();
		registry.emplace<Sample::Components::Building>(buildingEntity, "TownHall");
		registry.emplace<Sample::Components::HasOwner>(buildingEntity, provinceEntity);

		// Create a Turn event
		const auto turnEntity = registry.create();
		registry.emplace<Sample::Components::Turn>(turnEntity);

		// Create and run the BuildingIncomeSystem
		Sample::Systems::Buildings::BuildingIncomeSystem buildingIncomeSystem{registry};
		buildingIncomeSystem.Update();

		// Check if the income has been added to the player's resources
		const auto &resourceHolder = registry.get<Sample::Components::ResourceHolder>(playerEntity);
		auto it = resourceHolder.resources.find("Coins");
		ASSERT_NE(it, resourceHolder.resources.end());
		EXPECT_EQ(it->second, 100 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT);
	}

	TEST(EcsSampleBuildingIncomeSystemTest, NoIncomeWithoutTurn) {
		entt::registry registry;

		// Set up building config
		auto &ctx = registry.ctx();
		std::map<std::string, Sample::Configs::BuildingConfig> buildingConfigs;
		buildingConfigs["TownHall"] = Sample::Configs::BuildingConfig{
				"TownHall", {{"Coins", Sample::ResourceConstants::GetResourceUnits(100)}}};
		ctx.emplace<Sample::Configs::BuildingConfigProvider>(buildingConfigs);

		// Create a player entity with ResourceHolder
		const auto playerEntity = registry.create();
		std::map<std::string, long> playerResources;
		playerResources["Coins"] = 0;
		registry.emplace<Sample::Components::ResourceHolder>(playerEntity, playerResources);

		// Create a province entity owned by the player
		const auto provinceEntity = registry.create();
		registry.emplace<Sample::Components::Province>(provinceEntity);
		registry.emplace<Sample::Components::HasOwner>(provinceEntity, playerEntity);

		// Create a building entity in the province
		const auto buildingEntity = registry.create();
		registry.emplace<Sample::Components::Building>(buildingEntity, "TownHall");
		registry.emplace<Sample::Components::HasOwner>(buildingEntity, provinceEntity);

		// Create and run the BuildingIncomeSystem
		Sample::Systems::Buildings::BuildingIncomeSystem buildingIncomeSystem{registry};
		buildingIncomeSystem.Update();

		// Check if the income has not been added to the player's resources
		const auto &resourceHolder = registry.get<Sample::Components::ResourceHolder>(playerEntity);
		auto it = resourceHolder.resources.find("Coins");
		ASSERT_NE(it, resourceHolder.resources.end());
		EXPECT_EQ(it->second, 0);
	}
}
