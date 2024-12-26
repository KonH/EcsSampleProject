#pragma once

#include <gtest/gtest.h>
#include <entt/entt.hpp>

#include "Types/ControlType.h"

#include "Components/RenderSettings.h"
#include "Components/MousePosition.h"
#include "Components/ControlPress.h"
#include "Components/WorldPosition.h"
#include "Components/Army.h"
#include "Components/IsPlayer.h"
#include "Components/IsSelected.h"

#include "Systems/Selection/MouseArmySelectionSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleMouseArmySelectionSystemTest, IsPlayerArmySelectedOnMouseClick) {
		entt::registry registry;
		
		registry.ctx().emplace<Components::RenderSettings>();
		registry.ctx().get<Components::RenderSettings>().unitSize = 1.0f;
		registry.ctx().emplace<Components::MousePosition>(Types::Vector2Float { 0.0f, 0.0f });

		const auto playerArmy = registry.create();
		registry.emplace<Components::WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<Components::Army>(playerArmy);
		registry.emplace<Components::IsPlayer>(playerArmy);

		registry.emplace<Components::ControlPress>(registry.create(), Types::ControlType::LeftMouseButton);

		auto selectionSystem = Systems::Selection::MouseArmySelectionSystem { registry };

		selectionSystem.Update();

		EXPECT_TRUE(registry.all_of<Components::IsSelected>(playerArmy));
	}

	TEST(EcsSampleMouseArmySelectionSystemTest, IsPlayerArmyDeselectedOnMouseClick) {
		entt::registry registry;

		registry.ctx().emplace<Components::RenderSettings>();
		registry.ctx().get<Components::RenderSettings>().unitSize = 1.0f;
		registry.ctx().emplace<Components::MousePosition>(Types::Vector2Float { 0.0f, 0.0f });

		const auto playerArmy = registry.create();
		registry.emplace<Components::WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<Components::Army>(playerArmy);
		registry.emplace<Components::IsPlayer>(playerArmy);
		registry.emplace<Components::IsSelected>(playerArmy);

		registry.emplace<Components::ControlPress>(registry.create(), Types::ControlType::LeftMouseButton);

		auto selectionSystem = Systems::Selection::MouseArmySelectionSystem { registry };

		selectionSystem.Update();

		EXPECT_FALSE(registry.all_of<Components::IsSelected>(playerArmy));
	}
}