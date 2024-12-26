#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/CameraMovementIntent.h"
#include "Components/ControlDown.h"
#include "Components/MouseMove.h"
#include "Systems/Camera/CameraMovementIntentSystem.h"
#include "Types/ControlType.h"

namespace Sample::Tests {
	TEST(EcsSampleCameraMovementIntentSystemTest, CameraMovementIntentCreatedOnMouseMove) {
		entt::registry registry;

		const auto controlEntity = registry.create();
		registry.emplace<Components::ControlDown>(controlEntity, Sample::Types::ControlType::LeftMouseButton);

		const auto mouseMoveEntity = registry.create();
		registry.emplace<Components::MouseMove>(mouseMoveEntity, Types::Vector2Float{5.0f, 5.0f});

		Sample::Systems::Camera::CameraMovementIntentSystem system(registry);
		system.Update();

		auto view = registry.view<Components::CameraMovementIntent>();
		EXPECT_EQ(view.size(), 1);

		for (auto [entity, intent]: view.each()) {
			EXPECT_EQ(intent.wantedChange.x, 5);
			EXPECT_EQ(intent.wantedChange.y, 5);
		}
	}

	TEST(EcsSampleCameraMovementIntentSystemTest, NoCameraMovementIntentCreatedWithoutControlDown) {
		entt::registry registry;

		const auto mouseMoveEntity = registry.create();
		registry.emplace<Components::MouseMove>(mouseMoveEntity, Types::Vector2Float{5.0f, 5.0f});

		Sample::Systems::Camera::CameraMovementIntentSystem system(registry);
		system.Update();

		auto view = registry.view<Components::CameraMovementIntent>();
		EXPECT_EQ(view.size(), 0);
	}

	TEST(EcsSampleCameraMovementIntentSystemTest, NoCameraMovementIntentCreatedWithDifferentControl) {
		entt::registry registry;

		const auto controlEntity = registry.create();
		registry.emplace<Components::ControlDown>(controlEntity, Sample::Types::ControlType::Right);

		const auto mouseMoveEntity = registry.create();
		registry.emplace<Components::MouseMove>(mouseMoveEntity, Types::Vector2Float{5.0f, 5.0f});

		Sample::Systems::Camera::CameraMovementIntentSystem system(registry);
		system.Update();

		auto view = registry.view<Components::CameraMovementIntent>();
		EXPECT_EQ(view.size(), 0);
	}
}
