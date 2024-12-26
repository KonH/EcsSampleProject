#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/WorldPosition.h"
#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"

#include "Systems/Utility/ActionProgressCleanUpSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleActionProgressCleanUpSystemTest, RemoveActionProgressWhenFinished) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, 0.0f, 0.0f);
		registry.emplace<Components::ActionProgress>(entity);
		registry.emplace<Components::ActionFinish>(entity);

		auto cleanUpSystem = Systems::Utility::ActionProgressCleanUpSystem{registry};

		cleanUpSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::ActionProgress>(entity));
		EXPECT_TRUE(registry.valid(entity));
	}

	TEST(EcsSampleActionProgressCleanUpSystemTest, DestroyOrphanEntity) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ActionProgress>(entity);
		registry.emplace<Components::ActionFinish>(entity);

		auto cleanUpSystem = Systems::Utility::ActionProgressCleanUpSystem{registry};

		cleanUpSystem.Update();

		EXPECT_FALSE(registry.valid(entity));
	}
}
