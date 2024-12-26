#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/RenderSettings.h"
#include "Components/ScreenPositionSet.h"
#include "Components/WorldPositionSet.h"
#include "Systems/Presentation/WorldToScreenPositionSetSystem.h"
#include "Utils/VectorUtils.h"

namespace Sample::Tests {
	TEST(EcsSampleWorldToScreenPositionSetSystemTest, ScreenPositionsUpdated) {
		entt::registry registry;
		auto &renderSettings = registry.ctx().emplace<Components::RenderSettings>();
		renderSettings.unitSize = 1.0f;
		renderSettings.screenWidth = 800;
		renderSettings.screenHeight = 600;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPositionSet>(
				entity, std::vector<Types::Vector2Float>{{100.0f, 100.0f}, {200.0f, 200.0f}});
		registry.emplace<Components::ScreenPositionSet>(entity, std::vector<Types::Vector2Int>{});

		Sample::Systems::Presentation::WorldToScreenPositionSetSystem system(registry);
		system.Update();

		const auto &screenPositionSet = registry.get<Components::ScreenPositionSet>(entity);
		const auto center = VectorUtils::GetScreenCenter(renderSettings);
		const auto expectedScreenPosition1 =
				VectorUtils::ToScreenPosition(renderSettings, center, Types::Vector2Float{100.0f, 100.0f});
		const auto expectedScreenPosition2 =
				VectorUtils::ToScreenPosition(renderSettings, center, Types::Vector2Float{200.0f, 200.0f});

		EXPECT_EQ(screenPositionSet.positions.size(), 2);
		EXPECT_EQ(screenPositionSet.positions[0].x, expectedScreenPosition1.x);
		EXPECT_EQ(screenPositionSet.positions[0].y, expectedScreenPosition1.y);
		EXPECT_EQ(screenPositionSet.positions[1].x, expectedScreenPosition2.x);
		EXPECT_EQ(screenPositionSet.positions[1].y, expectedScreenPosition2.y);
	}
}
