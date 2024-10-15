#pragma once

#include <gtest/gtest.h>
#include <entt/entt.hpp>

#include "Components/ControlDown.h"
#include "Components/IsPlayer.h"
#include "Components/WorldPosition.h"
#include "Components/WorldMovementIntent.h"
#include "Systems/Movement/PlayerMovementSystem.h"
#include "Types/ControlType.h"

namespace Sample::Tests {
	TEST(EcsSamplePlayerMovementSystemTest, PlayerMovesRightWhenRightControlIsPressed) {
		entt::registry registry;
		auto movementSystem = Systems::Movement::PlayerMovementSystem { registry };
		const auto playerEntity = registry.create();
		const auto controlEntity = registry.create();

		registry.emplace<Components::IsPlayer>(playerEntity);
		registry.emplace<Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Components::ControlDown>(controlEntity, Types::ControlType::Right);

		movementSystem.Update();

		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerEntity));
		const auto& movementIntent = registry.get<Components::WorldMovementIntent>(playerEntity);
		EXPECT_EQ(movementIntent.wantedChange.x, 1.0f);
		EXPECT_EQ(movementIntent.wantedChange.y, 0.0f);
	}
}