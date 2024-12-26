#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/IsObstacle.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

#include "Systems/Movement/ObstacleFilterSystem.h"

namespace Sample::Tests {
	TEST(ObstacleFilterSystemTest, RemoveMovementIntentWhenObstaclePresent) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, Types::Vector2Float{0.0f, 0.0f});
		registry.emplace<Components::WorldMovementIntent>(entity, Types::Vector2Float{1.0f, 0.0f});

		const auto obstacleEntity = registry.create();
		registry.emplace<Components::WorldPosition>(obstacleEntity, Types::Vector2Float{1.0f, 0.0f});
		registry.emplace<Components::IsObstacle>(obstacleEntity);

		auto obstacleFilterSystem = Systems::Movement::ObstacleFilterSystem{registry};

		obstacleFilterSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::WorldMovementIntent>(entity));
	}

	TEST(ObstacleFilterSystemTest, KeepMovementIntentWhenNoObstacle) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, Types::Vector2Float{0.0f, 0.0f});
		registry.emplace<Components::WorldMovementIntent>(entity, Types::Vector2Float{1.0f, 0.0f});

		const auto obstacleEntity = registry.create();
		registry.emplace<Components::WorldPosition>(obstacleEntity, Types::Vector2Float{2.0f, 0.0f});
		registry.emplace<Components::IsObstacle>(obstacleEntity);

		auto obstacleFilterSystem = Systems::Movement::ObstacleFilterSystem{registry};

		obstacleFilterSystem.Update();

		EXPECT_TRUE(registry.all_of<Components::WorldMovementIntent>(entity));
	}
}
