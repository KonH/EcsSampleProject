#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Common/ResourceConstants.h"

#include "Components/ResourceCounter.h"
#include "Components/ResourceHolder.h"
#include "Components/Text.h"

#include "Systems/Presentation/ResourceCounterUpdateSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleResourceCounterUpdateSystemTest, UpdateResourceCounterText) {
		entt::registry registry;

		const auto player = registry.create();
		std::map<std::string, long> resources;
		resources["Coins"] = static_cast<long>(100 * ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT);
		registry.emplace<Components::ResourceHolder>(player, resources);

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "Coins", player);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		resourceCounterUpdateSystem.Update();

		const auto &text = registry.get<Components::Text>(resourceCounterEntity);
		EXPECT_EQ(text.text, "Coins: 100");
	}

	TEST(EcsSampleResourceCounterUpdateSystemTest, UpdateResourceCounterTextWithFraction) {
		entt::registry registry;

		const auto player = registry.create();
		std::map<std::string, long> resources;
		resources["Coins"] = static_cast<long>(123.45 * ResourceConstants::RESOURCE_UNITS_PER_DISPLAY_UNIT);
		registry.emplace<Components::ResourceHolder>(player, resources);

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "Coins", player);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		resourceCounterUpdateSystem.Update();

		const auto &text = registry.get<Components::Text>(resourceCounterEntity);
		EXPECT_EQ(text.text, "Coins: 123.45");
	}

	TEST(EcsSampleResourceCounterUpdateSystemTest, InvalidResourceOwner) {
		entt::registry registry;

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "Coins", entt::null);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		resourceCounterUpdateSystem.Update();

		const auto &text = registry.get<Components::Text>(resourceCounterEntity);
		EXPECT_EQ(text.text, "");
	}

	TEST(EcsSampleResourceCounterUpdateSystemTest, InvalidResourceId) {
		entt::registry registry;

		const auto player = registry.create();
		std::map<std::string, long> resources;
		registry.emplace<Components::ResourceHolder>(player, resources);

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "InvalidResource", player);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		resourceCounterUpdateSystem.Update();

		const auto &text = registry.get<Components::Text>(resourceCounterEntity);
		EXPECT_EQ(text.text, "");
	}
}
