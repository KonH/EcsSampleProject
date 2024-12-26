#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"
#include "Components/WorldMovement.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

#include "Systems/Movement/WorldMovementSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleWorldMovementSystemTest, ApplyMovementIntent) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::WorldMovementIntent>(entity, Types::Vector2Float{5.0f, 5.0f});

		auto movementSystem = Systems::Movement::WorldMovementSystem{registry};

		movementSystem.Update();

		EXPECT_TRUE(registry.all_of<Components::WorldMovement>(entity));
		EXPECT_TRUE(registry.all_of<Components::ActionProgress>(entity));
		EXPECT_TRUE(registry.all_of<Components::ActionStart>(entity));

		const auto &movement = registry.get<Components::WorldMovement>(entity);
		EXPECT_EQ(movement.change.x, 5.0f);
		EXPECT_EQ(movement.change.y, 5.0f);
	}

	TEST(EcsSampleWorldMovementSystemTest, ApplyNewPosition) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, Types::Vector2Float{0.0f, 0.0f});
		registry.emplace<Components::WorldMovement>(entity, Types::Vector2Float{5.0f, 5.0f});
		registry.emplace<Components::ActionFinish>(entity);

		auto movementSystem = Systems::Movement::WorldMovementSystem{registry};

		movementSystem.Update();

		const auto &position = registry.get<Components::WorldPosition>(entity);
		EXPECT_EQ(position.position.x, 5.0f);
		EXPECT_EQ(position.position.y, 5.0f);

		EXPECT_FALSE(registry.all_of<Components::WorldMovement>(entity));
	}
}
