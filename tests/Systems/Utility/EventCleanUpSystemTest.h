#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ActionFinish.h"
#include "Components/ActionStart.h"
#include "Components/CameraMovement.h"
#include "Components/CameraMovementIntent.h"
#include "Components/ControlDown.h"
#include "Components/ControlPress.h"
#include "Components/MouseMove.h"
#include "Components/MouseScroll.h"
#include "Components/WorldMovementIntent.h"

#include "Systems/Utility/EventCleanUpSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleEventCleanUpSystemTest, CleanUpControlPress) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ControlPress>(entity);

		auto cleanUpSystem = Systems::Utility::EventCleanUpSystem{registry};

		cleanUpSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::ControlPress>(entity));
	}

	TEST(EcsSampleEventCleanUpSystemTest, CleanUpActionFinish) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ActionFinish>(entity);

		auto cleanUpSystem = Systems::Utility::EventCleanUpSystem{registry};

		cleanUpSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::ActionFinish>(entity));
	}

	TEST(EcsSampleEventCleanUpSystemTest, CleanUpAllEvents) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ControlPress>(entity);
		registry.emplace<Components::ControlDown>(entity);
		registry.emplace<Components::MouseScroll>(entity);
		registry.emplace<Components::MouseMove>(entity);
		registry.emplace<Components::ActionStart>(entity);
		registry.emplace<Components::ActionFinish>(entity);
		registry.emplace<Components::WorldMovementIntent>(entity);
		registry.emplace<Components::CameraMovementIntent>(entity);
		registry.emplace<Components::CameraMovement>(entity);

		auto cleanUpSystem = Systems::Utility::EventCleanUpSystem{registry};

		cleanUpSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::ControlPress>(entity));
		EXPECT_FALSE(registry.all_of<Components::ControlDown>(entity));
		EXPECT_FALSE(registry.all_of<Components::MouseScroll>(entity));
		EXPECT_FALSE(registry.all_of<Components::MouseMove>(entity));
		EXPECT_FALSE(registry.all_of<Components::ActionStart>(entity));
		EXPECT_FALSE(registry.all_of<Components::ActionFinish>(entity));
		EXPECT_FALSE(registry.all_of<Components::WorldMovementIntent>(entity));
		EXPECT_FALSE(registry.all_of<Components::CameraMovementIntent>(entity));
		EXPECT_FALSE(registry.all_of<Components::CameraMovement>(entity));
	}
}
