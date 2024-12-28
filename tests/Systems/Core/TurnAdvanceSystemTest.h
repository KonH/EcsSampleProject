#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Common/ResourceConstants.h"
#include "Components/Click.h"
#include "Components/NextTurnButton.h"
#include "Components/ResourceHolder.h"
#include "Systems/Core/TurnAdvanceSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleTurnAdvanceSystemTest, TurnIsAdvancedOnClick) {
		entt::registry registry;

		// Create an entity with NextTurnButton and Click
		const auto nextTurnButtonEntity = registry.create();
		registry.emplace<Sample::Components::NextTurnButton>(nextTurnButtonEntity);
		registry.emplace<Sample::Components::Click>(nextTurnButtonEntity);

		// Create an entity with ResourceHolder
		const auto resourceHolderEntity = registry.create();
		std::map<std::string, long> resources;
		resources["Turns"] = 1 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT;
		registry.emplace<Sample::Components::ResourceHolder>(resourceHolderEntity, resources);

		// Create and run the TurnAdvanceSystem
		Sample::Systems::Core::TurnAdvanceSystem turnAdvanceSystem{registry};
		turnAdvanceSystem.Update();

		// Check if the "Turns" resource has been incremented
		const auto &resourceHolder = registry.get<Sample::Components::ResourceHolder>(resourceHolderEntity);
		auto it = resourceHolder.resources.find("Turns");
		ASSERT_NE(it, resourceHolder.resources.end());
		EXPECT_EQ(it->second, 2 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT);
	}

	TEST(EcsSampleTurnAdvanceSystemTest, NoTurnAdvanceWithoutClick) {
		entt::registry registry;

		// Create an entity with NextTurnButton but without Click
		const auto nextTurnButtonEntity = registry.create();
		registry.emplace<Sample::Components::NextTurnButton>(nextTurnButtonEntity);

		// Create an entity with ResourceHolder
		const auto resourceHolderEntity = registry.create();
		std::map<std::string, long> resources;
		resources["Turns"] = 1 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT;
		registry.emplace<Sample::Components::ResourceHolder>(resourceHolderEntity, resources);

		// Create and run the TurnAdvanceSystem
		Sample::Systems::Core::TurnAdvanceSystem turnAdvanceSystem{registry};
		turnAdvanceSystem.Update();

		// Check if the "Turns" resource has not been incremented
		const auto &resourceHolder = registry.get<Sample::Components::ResourceHolder>(resourceHolderEntity);
		auto it = resourceHolder.resources.find("Turns");
		ASSERT_NE(it, resourceHolder.resources.end());
		EXPECT_EQ(it->second, 1 * Sample::ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT);
	}
}
