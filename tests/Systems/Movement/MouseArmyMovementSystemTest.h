#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Types/ControlType.h"
#include "Types/Vector2Float.h"

#include "Components/Army.h"
#include "Components/ControlPress.h"
#include "Components/HasOwner.h"
#include "Components/IsPlayer.h"
#include "Components/IsSelected.h"
#include "Components/MousePosition.h"
#include "Components/Province.h"
#include "Components/RenderSettings.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"

#include "Systems/Movement/MouseArmyMovementSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleMouseArmyMovementTest, PlayerArmyMovesToUnownedProvinceOnMouseClick) {
		entt::registry registry;

		// Set up render settings and mouse position
		registry.ctx().emplace<Components::RenderSettings>();
		registry.ctx().get<Components::RenderSettings>().unitSize = 1.0f;
		registry.ctx().emplace<Components::MousePosition>(Types::Vector2Float{1.0f, 0.0f});

		// Create player entity
		const auto playerEntity = registry.create();

		// Create player army entity
		const auto playerArmy = registry.create();
		registry.emplace<Components::WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<Components::Army>(playerArmy);
		registry.emplace<Components::IsPlayer>(playerArmy);
		registry.emplace<Components::HasOwner>(playerArmy, playerEntity);
		registry.emplace<Components::IsSelected>(playerArmy);

		// Create unowned province entity
		const auto unownedProvince = registry.create();
		registry.emplace<Components::Province>(unownedProvince);
		registry.emplace<Components::WorldPosition>(unownedProvince, 1.0f, 0.0f);

		// Simulate mouse click
		registry.emplace<Components::ControlPress>(registry.create(), Types::ControlType::LeftMouseButton);

		// Create and run the movement system
		auto movementSystem = Systems::Movement::MouseArmyMovementSystem{registry};
		movementSystem.Update();

		// Check if the movement intent has been created for the player army
		ASSERT_TRUE(registry.all_of<Components::WorldMovementIntent>(playerArmy));
		const auto &movementIntent = registry.get<Components::WorldMovementIntent>(playerArmy);
		auto wantedChange = Types::Vector2Float{1.0f, 0.0f};
		EXPECT_EQ(movementIntent.wantedChange, wantedChange);
	}
} // namespace Sample::Tests
