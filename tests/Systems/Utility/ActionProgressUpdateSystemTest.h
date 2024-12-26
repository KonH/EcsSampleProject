#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/Runtime.h"

#include "Systems/Utility/ActionProgressUpdateSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleActionProgressUpdateSystemTest, UpdateActionProgress) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ActionProgress>(entity, 0.0f, 1.0f);
		registry.ctx().emplace<Components::Runtime>(true, 0.5f);

		auto updateSystem = Systems::Utility::ActionProgressUpdateSystem{registry};

		updateSystem.Update();

		const auto &progress = registry.get<Components::ActionProgress>(entity);
		EXPECT_FLOAT_EQ(progress.progress, 0.5f);
		EXPECT_FALSE(registry.all_of<Components::ActionFinish>(entity));
	}

	TEST(EcsSampleActionProgressUpdateSystemTest, CompleteActionProgress) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ActionProgress>(entity, 0.0f, 1.0f);
		registry.ctx().emplace<Components::Runtime>(true, 1.0f);

		auto updateSystem = Systems::Utility::ActionProgressUpdateSystem{registry};

		updateSystem.Update();

		EXPECT_TRUE(registry.all_of<Components::ActionFinish>(entity));
	}
}
