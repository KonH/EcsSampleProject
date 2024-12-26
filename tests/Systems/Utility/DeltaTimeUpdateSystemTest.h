#pragma once

#include <chrono>
#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/Runtime.h"
#include "Systems/Utility/DeltaTimeUpdateSystem.h"

namespace Sample::Tests {
	TEST(DeltaTimeUpdateSystemTest, UpdateDeltaTime) {
		entt::registry registry;

		registry.ctx().emplace<Components::Runtime>();

		auto deltaTimeUpdateSystem = Systems::Utility::DeltaTimeUpdateSystem{registry};

		// Simulate the first update
		deltaTimeUpdateSystem.Update();

		// Wait for a short duration
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		// Simulate the second update
		deltaTimeUpdateSystem.Update();

		const auto &runtime = registry.ctx().get<Components::Runtime>();
		EXPECT_NEAR(runtime.deltaTime, 0.016f, 0.05f);
	}

	TEST(DeltaTimeUpdateSystemTest, InitialDeltaTimeIsZero) {
		entt::registry registry;

		registry.ctx().emplace<Components::Runtime>();

		auto deltaTimeUpdateSystem = Systems::Utility::DeltaTimeUpdateSystem{registry};

		deltaTimeUpdateSystem.Update();

		const auto &runtime = registry.ctx().get<Components::Runtime>();
		EXPECT_FLOAT_EQ(runtime.deltaTime, 0.0f);
	}
}
