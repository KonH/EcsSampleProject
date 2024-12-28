#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/HighlightColor.h"
#include "Components/IsSelected.h"
#include "Components/RenderColor.h"

#include "Systems/Presentation/HighlightSelectedSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleHighlightSelectedSystemTest, HighlightSelectedEntities) {
		entt::registry registry;

		// Create an entity with HighlightColor, RenderColor, and IsSelected
		const auto entity = registry.create();
		registry.emplace<Components::HighlightColor>(entity, Types::Color{255, 0, 0, 255},
													 Types::Color{0, 0, 255, 255});
		registry.emplace<Components::RenderColor>(entity, Types::Color{0, 0, 255, 255});
		registry.emplace<Components::IsSelected>(entity);

		// Create and run the HighlightSelectedSystem
		Sample::Systems::Presentation::HighlightSelectedSystem highlightSelectedSystem{registry};
		highlightSelectedSystem.Update();

		// Check if the render color has been updated to the highlight color
		const auto &renderColor = registry.get<Components::RenderColor>(entity);
		EXPECT_EQ(renderColor.color.red, 255);
		EXPECT_EQ(renderColor.color.green, 0);
		EXPECT_EQ(renderColor.color.blue, 0);
		EXPECT_EQ(renderColor.color.alpha, 255);
	}

	TEST(EcsSampleHighlightSelectedSystemTest, RevertHighlightForDeselectedEntities) {
		entt::registry registry;

		// Create an entity with HighlightColor and RenderColor, but without IsSelected
		const auto entity = registry.create();
		registry.emplace<Components::HighlightColor>(entity, Types::Color{255, 0, 0, 255},
													 Types::Color{0, 0, 255, 255});
		registry.emplace<Components::RenderColor>(entity, Types::Color{255, 0, 0, 255});

		// Create and run the HighlightSelectedSystem
		Sample::Systems::Presentation::HighlightSelectedSystem highlightSelectedSystem{registry};
		highlightSelectedSystem.Update();

		// Check if the render color has been reverted to the default color
		const auto &renderColor = registry.get<Components::RenderColor>(entity);
		EXPECT_EQ(renderColor.color.red, 0);
		EXPECT_EQ(renderColor.color.green, 0);
		EXPECT_EQ(renderColor.color.blue, 255);
		EXPECT_EQ(renderColor.color.alpha, 255);
	}
}
