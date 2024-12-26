#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>
#include <tweeny.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"
#include "Components/RenderSettings.h"
#include "Components/ScreenOffset.h"
#include "Components/WorldMovement.h"
#include "Components/WorldMovementAnimation.h"
#include "Components/WorldPosition.h"
#include "Systems/Animation/MovementAnimationSystem.h"

namespace Sample::Tests {
	TEST(MovementAnimationSystemTest, AnimationStartsCorrectly) {
		entt::registry registry;
		registry.ctx().emplace<Components::RenderSettings>().unitSize = 1.0f;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, 0.0f, 0.0f);
		registry.emplace<Components::WorldMovement>(entity, Types::Vector2Float{10.0f, 10.0f});
		registry.emplace<Components::ActionProgress>(entity, 0.0f, 1.0f);
		registry.emplace<Components::ActionStart>(entity);

		Sample::Systems::Animation::MovementAnimationSystem system(registry);
		system.Update();

		EXPECT_TRUE(registry.all_of<Components::WorldMovementAnimation>(entity));
		EXPECT_TRUE(registry.all_of<Components::ScreenOffset>(entity));
	}

	TEST(MovementAnimationSystemTest, AnimationUpdatesCorrectly) {
		entt::registry registry;
		registry.ctx().emplace<Components::RenderSettings>().unitSize = 1.0f;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, 0.0f, 0.0f);
		registry.emplace<Components::WorldMovement>(entity, Types::Vector2Float{10.0f, 10.0f});
		registry.emplace<Components::ActionProgress>(entity, 0.5f, 1.0f);
		registry.emplace<Components::WorldMovementAnimation>(
				entity, tweeny::from(0.0f, 0.0f).to(10.0f, 10.0f).during(1000).via(tweeny::easing::bounceOut));
		registry.emplace<Components::ScreenOffset>(entity, 0, 0);

		Sample::Systems::Animation::MovementAnimationSystem system(registry);
		system.Update();

		const auto &offset = registry.get<Components::ScreenOffset>(entity);
		EXPECT_NE(offset.offset.x, 0);
		EXPECT_NE(offset.offset.y, 0);
	}

	TEST(MovementAnimationSystemTest, AnimationFinishesCorrectly) {
		entt::registry registry;
		registry.ctx().emplace<Components::RenderSettings>().unitSize = 1.0f;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, 0.0f, 0.0f);
		registry.emplace<Components::WorldMovement>(entity, Types::Vector2Float{10.0f, 10.0f});
		registry.emplace<Components::ActionProgress>(entity, 1.0f, 1.0f);
		registry.emplace<Components::WorldMovementAnimation>(
				entity, tweeny::from(0.0f, 0.0f).to(10.0f, 10.0f).during(1000).via(tweeny::easing::bounceOut));
		registry.emplace<Components::ScreenOffset>(entity, 0, 0);
		registry.emplace<Components::ActionFinish>(entity);

		Sample::Systems::Animation::MovementAnimationSystem system(registry);
		system.Update();

		EXPECT_FALSE(registry.all_of<Components::WorldMovementAnimation>(entity));
		EXPECT_FALSE(registry.all_of<Components::ScreenOffset>(entity));
	}
}
