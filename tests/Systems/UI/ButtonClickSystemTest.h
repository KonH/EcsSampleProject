#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/BoxCollider.h"
#include "Components/Button.h"
#include "Components/Click.h"
#include "Components/ControlPress.h"
#include "Components/MousePosition.h"
#include "Components/ScreenPosition.h"
#include "Systems/UI/ButtonClickSystem.h"
#include "Types/ControlType.h"
#include "Types/Vector2Float.h"
#include "Types/Vector2Int.h"

namespace Sample::Tests {
	TEST(EcsSampleButtonClickSystemTest, ButtonClickGeneratesClickEvent) {
		entt::registry registry;

		// Set up initial mouse position
		auto &ctx = registry.ctx();
		ctx.emplace<Sample::Components::MousePosition>(Sample::Types::Vector2Float{50.0f, 50.0f});

		// Create an entity with Button, BoxCollider, and ScreenPosition
		const auto buttonEntity = registry.create();
		registry.emplace<Sample::Components::Button>(buttonEntity);
		registry.emplace<Sample::Components::BoxCollider>(buttonEntity, Sample::Types::Vector2Int{100, 50});
		registry.emplace<Sample::Components::ScreenPosition>(buttonEntity, Sample::Types::Vector2Int{0, 0});

		// Create a ControlPress entity for left mouse button click
		const auto controlPressEntity = registry.create();
		registry.emplace<Sample::Components::ControlPress>(controlPressEntity,
														   Sample::Types::ControlType::LeftMouseButton);

		// Create and run the ButtonClickSystem
		Sample::Systems::UI::ButtonClickSystem buttonClickSystem{registry};
		buttonClickSystem.Update();

		// Check if the Click event has been generated on the button entity
		ASSERT_TRUE(registry.all_of<Sample::Components::Click>(buttonEntity));
	}

	TEST(EcsSampleButtonClickSystemTest, ButtonClickOutsideBoundsDoesNotGenerateClickEvent) {
		entt::registry registry;

		// Set up initial mouse position
		auto &ctx = registry.ctx();
		ctx.emplace<Sample::Components::MousePosition>(Sample::Types::Vector2Float{200.0f, 200.0f});

		// Create an entity with Button, BoxCollider, and ScreenPosition
		const auto buttonEntity = registry.create();
		registry.emplace<Sample::Components::Button>(buttonEntity);
		registry.emplace<Sample::Components::BoxCollider>(buttonEntity, Sample::Types::Vector2Int{100, 50});
		registry.emplace<Sample::Components::ScreenPosition>(buttonEntity, Sample::Types::Vector2Int{0, 0});

		// Create a ControlPress entity for left mouse button click
		const auto controlPressEntity = registry.create();
		registry.emplace<Sample::Components::ControlPress>(controlPressEntity,
														   Sample::Types::ControlType::LeftMouseButton);

		// Create and run the ButtonClickSystem
		Sample::Systems::UI::ButtonClickSystem buttonClickSystem{registry};
		buttonClickSystem.Update();

		// Check if the Click event has not been generated on the button entity
		ASSERT_FALSE(registry.all_of<Sample::Components::Click>(buttonEntity));
	}
}
