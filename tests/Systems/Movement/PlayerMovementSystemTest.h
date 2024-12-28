#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ControlDown.h"
#include "Components/IsPlayer.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"
#include "Systems/Movement/PlayerMovementSystem.h"
#include "Types/ControlType.h"

namespace Sample::Tests {
	TEST(EcsSamplePlayerMovementSystemTest, PlayerMovesRightWhenRightControlIsPressed) {
		entt::registry registry;
		auto movementSystem = Systems::Movement::PlayerMovementSystem{registry};
		const auto playerEntity = registry.create();
		const auto controlEntity = registry.create();

		registry.emplace<Components::IsPlayer>(playerEntity);
		registry.emplace<Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Components::ControlDown>(controlEntity, Types::ControlType::Right);

		movementSystem.Update();

		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerEntity));
		const auto &movementIntent = registry.get<Components::WorldMovementIntent>(playerEntity);
		EXPECT_EQ(movementIntent.wantedChange.x, 1.0f);
		EXPECT_EQ(movementIntent.wantedChange.y, 0.0f);
	}

	TEST(EcsSamplePlayerMovementSystemTest, PlayerMovesLeftWhenLeftControlIsPressed) {
		entt::registry registry;
		auto movementSystem = Systems::Movement::PlayerMovementSystem{registry};
		const auto playerEntity = registry.create();
		const auto controlEntity = registry.create();

		registry.emplace<Components::IsPlayer>(playerEntity);
		registry.emplace<Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Components::ControlDown>(controlEntity, Types::ControlType::Left);

		movementSystem.Update();

		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerEntity));
		const auto &movementIntent = registry.get<Components::WorldMovementIntent>(playerEntity);
		EXPECT_EQ(movementIntent.wantedChange.x, -1.0f);
		EXPECT_EQ(movementIntent.wantedChange.y, 0.0f);
	}

	TEST(EcsSamplePlayerMovementSystemTest, PlayerMovesUpWhenUpControlIsPressed) {
		entt::registry registry;
		auto movementSystem = Systems::Movement::PlayerMovementSystem{registry};
		const auto playerEntity = registry.create();
		const auto controlEntity = registry.create();

		registry.emplace<Components::IsPlayer>(playerEntity);
		registry.emplace<Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Components::ControlDown>(controlEntity, Types::ControlType::Up);

		movementSystem.Update();

		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerEntity));
		const auto &movementIntent = registry.get<Components::WorldMovementIntent>(playerEntity);
		EXPECT_EQ(movementIntent.wantedChange.x, 0.0f);
		EXPECT_EQ(movementIntent.wantedChange.y, -1.0f);
	}

	TEST(EcsSamplePlayerMovementSystemTest, PlayerMovesDownWhenDownControlIsPressed) {
		entt::registry registry;
		auto movementSystem = Systems::Movement::PlayerMovementSystem{registry};
		const auto playerEntity = registry.create();
		const auto controlEntity = registry.create();

		registry.emplace<Components::IsPlayer>(playerEntity);
		registry.emplace<Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Components::ControlDown>(controlEntity, Types::ControlType::Down);

		movementSystem.Update();

		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerEntity));
		const auto &movementIntent = registry.get<Components::WorldMovementIntent>(playerEntity);
		EXPECT_EQ(movementIntent.wantedChange.x, 0.0f);
		EXPECT_EQ(movementIntent.wantedChange.y, 1.0f);
	}
}
