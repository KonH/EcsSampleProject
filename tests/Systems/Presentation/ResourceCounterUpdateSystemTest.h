#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ResourceCounter.h"
#include "Components/ResourceHolder.h"
#include "Components/Text.h"

#include "Systems/Presentation/ResourceCounterUpdateSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleResourceCounterUpdateSystemTest, UpdateResourceCounterText) {
		entt::registry registry;

		const auto player = registry.create();
		std::map<std::string, long> resources;
		resources["Coins"] = 100;
		registry.emplace<Components::ResourceHolder>(player, resources);

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "Coins", player);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		resourceCounterUpdateSystem.Update();

		const auto &text = registry.get<Components::Text>(resourceCounterEntity);
		EXPECT_EQ(text.text, "Coins: 100");
	}

	TEST(EcsSampleResourceCounterUpdateSystemTest, InvalidResourceOwner) {
		entt::registry registry;

		const auto resourceCounterEntity = registry.create();
		registry.emplace<Components::ResourceCounter>(resourceCounterEntity, "Coins", entt::null);
		registry.emplace<Components::Text>(resourceCounterEntity, "Roboto-Black.ttf", 25, "");

		auto resourceCounterUpdateSystem = Systems::Presentation::ResourceCounterUpdateSystem{registry};

		EXPECT_DEATH(resourceCounterUpdateSystem.Update(), "Resource owner entity is invalid");
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

		EXPECT_DEATH(resourceCounterUpdateSystem.Update(), "Resource ID is invalid");
	}
}
