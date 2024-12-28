#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/IsHighlightCell.h"
#include "Components/MousePosition.h"
#include "Components/RenderSettings.h"
#include "Components/WorldPosition.h"

#include "Systems/Presentation/HighlightCellByMousePositionSystem.h"
#include "Types/Vector2Float.h"
#include "Utils/VectorUtils.h"

namespace Sample::Tests {
	TEST(EcsSampleHighlightCellByMousePositionSystemTest, HighlightCellFollowsMousePosition) {
		entt::registry registry;

		// Set up initial render settings
		auto &ctx = registry.ctx();
		ctx.emplace<Components::RenderSettings>("ECS Sample Project", // windowTitle
												1200u, // screenWidth
												800u, // screenHeight
												50.f, // unitSize
												Types::Vector2Float{0.0f, 0.0f} // cameraCenter
		);

		// Set up initial mouse position
		ctx.emplace<Components::MousePosition>(Types::Vector2Float{600.0f, 400.0f});

		// Create an entity with WorldPosition and IsHighlightCell
		const auto entity = registry.create();
		registry.emplace<Components::WorldPosition>(entity, Types::Vector2Float{0.0f, 0.0f});
		registry.emplace<Components::IsHighlightCell>(entity);

		// Create and run the HighlightCellByMousePositionSystem
		Sample::Systems::Presentation::HighlightCellByMousePositionSystem highlightCellByMousePositionSystem{registry};
		highlightCellByMousePositionSystem.Update();

		// Check if the world position has been updated to follow the mouse position
		const auto &worldPosition = registry.get<Components::WorldPosition>(entity);
		EXPECT_FLOAT_EQ(worldPosition.position.x, 0.0f);
		EXPECT_FLOAT_EQ(worldPosition.position.y, 0.0f);
	}
}
