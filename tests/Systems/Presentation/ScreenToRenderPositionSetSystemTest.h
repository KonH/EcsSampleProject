#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/RenderPositionSet.h"
#include "Components/ScreenOffset.h"
#include "Components/ScreenPositionSet.h"
#include "Systems/Presentation/ScreenToRenderPositionSetSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleScreenToRenderPositionSetSystemTest, RenderPositionsUpdatedWithoutOffset) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ScreenPositionSet>(entity, std::vector<Types::Vector2Int>{{10, 20}, {30, 40}});
		registry.emplace<Components::RenderPositionSet>(entity, std::vector<Types::Vector2Int>{});

		Sample::Systems::Presentation::ScreenToRenderPositionSetSystem system(registry);
		system.Update();

		const auto &renderPositionSet = registry.get<Components::RenderPositionSet>(entity);
		EXPECT_EQ(renderPositionSet.positions.size(), 2);
		EXPECT_EQ(renderPositionSet.positions[0].x, 10);
		EXPECT_EQ(renderPositionSet.positions[0].y, 20);
		EXPECT_EQ(renderPositionSet.positions[1].x, 30);
		EXPECT_EQ(renderPositionSet.positions[1].y, 40);
	}

	TEST(EcsSampleScreenToRenderPositionSetSystemTest, RenderPositionsUpdatedWithOffset) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ScreenPositionSet>(entity, std::vector<Types::Vector2Int>{{10, 20}, {30, 40}});
		registry.emplace<Components::RenderPositionSet>(entity, std::vector<Types::Vector2Int>{});
		registry.emplace<Components::ScreenOffset>(entity, Types::Vector2Int{5, 5});

		Sample::Systems::Presentation::ScreenToRenderPositionSetSystem system(registry);
		system.Update();

		const auto &renderPositionSet = registry.get<Components::RenderPositionSet>(entity);
		EXPECT_EQ(renderPositionSet.positions.size(), 2);
		EXPECT_EQ(renderPositionSet.positions[0].x, 15);
		EXPECT_EQ(renderPositionSet.positions[0].y, 25);
		EXPECT_EQ(renderPositionSet.positions[1].x, 35);
		EXPECT_EQ(renderPositionSet.positions[1].y, 45);
	}
}
