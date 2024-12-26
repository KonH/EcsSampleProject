#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/RenderPosition.h"
#include "Components/ScreenOffset.h"
#include "Components/ScreenPosition.h"
#include "Systems/Presentation/ScreenToRenderPositionSystem.h"

namespace Sample::Tests {
	TEST(ScreenToRenderPositionSystemTest, RenderPositionUpdatedWithoutOffset) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ScreenPosition>(entity, Types::Vector2Int{10, 20});
		registry.emplace<Components::RenderPosition>(entity, Types::Vector2Int{0, 0});

		Sample::Systems::Presentation::ScreenToRenderPositionSystem system(registry);
		system.Update();

		const auto &renderPosition = registry.get<Components::RenderPosition>(entity);
		EXPECT_EQ(renderPosition.position.x, 10);
		EXPECT_EQ(renderPosition.position.y, 20);
	}

	TEST(ScreenToRenderPositionSystemTest, RenderPositionUpdatedWithOffset) {
		entt::registry registry;

		const auto entity = registry.create();
		registry.emplace<Components::ScreenPosition>(entity, Types::Vector2Int{10, 20});
		registry.emplace<Components::RenderPosition>(entity, Types::Vector2Int{0, 0});
		registry.emplace<Components::ScreenOffset>(entity, Types::Vector2Int{5, 5});

		Sample::Systems::Presentation::ScreenToRenderPositionSystem system(registry);
		system.Update();

		const auto &renderPosition = registry.get<Components::RenderPosition>(entity);
		EXPECT_EQ(renderPosition.position.x, 15);
		EXPECT_EQ(renderPosition.position.y, 25);
	}
}
