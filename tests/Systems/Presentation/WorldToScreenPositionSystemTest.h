#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/RenderSettings.h"
#include "Components/ScreenPosition.h"
#include "Components/WorldPosition.h"
#include "Systems/Presentation/WorldToScreenPositionSystem.h"
#include "Utils/VectorUtils.h"

namespace Sample::Tests {
	TEST(EcsSampleWorldToScreenPositionSystemTest, ScreenPositionUpdated) {
		entt::registry registry;
		auto &renderSettings = registry.ctx().emplace<Components::RenderSettings>();
		renderSettings.unitSize = 1.0f;
		renderSettings.screenWidth = 800;
		renderSettings.screenHeight = 600;

		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, Types::Vector2Float{100.0f, 100.0f});
		registry.emplace<Components::ScreenPosition>(entity, Types::Vector2Int{0, 0});

		Sample::Systems::Presentation::WorldToScreenPositionSystem system(registry);
		system.Update();

		const auto &screenPosition = registry.get<Components::ScreenPosition>(entity);
		const auto center = VectorUtils::GetScreenCenter(renderSettings);
		const auto expectedScreenPosition =
				VectorUtils::ToScreenPosition(renderSettings, center, Types::Vector2Float{100.0f, 100.0f});

		EXPECT_EQ(screenPosition.position.x, expectedScreenPosition.x);
		EXPECT_EQ(screenPosition.position.y, expectedScreenPosition.y);
	}
}
