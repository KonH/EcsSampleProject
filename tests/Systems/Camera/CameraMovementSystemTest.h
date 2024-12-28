#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/CameraMovementIntent.h"
#include "Components/RenderSettings.h"

#include "Systems/Camera/CameraMovementSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleCameraMovementSystemTest, CameraMovesAccordingToIntent) {
		entt::registry registry;

		// Set up initial render settings
		auto &ctx = registry.ctx();
		ctx.emplace<Components::RenderSettings>("ECS Sample Project", // windowTitle
												1200u, // screenWidth
												800u, // screenHeight
												50.f, // unitSize
												Types::Vector2Float{0.0f, 0.0f} // cameraCenter
		);

		// Create an entity with CameraMovementIntent
		const auto entity = registry.create();
		registry.emplace<Components::CameraMovementIntent>(entity, Types::Vector2Float{10.0f, 5.0f});

		// Create and run the CameraMovementSystem
		Sample::Systems::Camera::CameraMovementSystem cameraMovementSystem{registry};
		cameraMovementSystem.Update();

		// Check if the camera center has moved according to the intent
		const auto &renderSettings = ctx.get<Components::RenderSettings>();
		EXPECT_EQ(renderSettings.cameraCenter.x, 10.0f);
		EXPECT_EQ(renderSettings.cameraCenter.y, 5.0f);
	}

	TEST(EcsSampleCameraMovementSystemTest, MultipleIntentsAreSummed) {
		entt::registry registry;

		// Set up initial render settings
		auto &ctx = registry.ctx();
		ctx.emplace<Components::RenderSettings>("ECS Sample Project", // windowTitle
												1200u, // screenWidth
												800u, // screenHeight
												50.f, // unitSize
												Types::Vector2Float{0.0f, 0.0f} // cameraCenter
		);

		// Create multiple entities with CameraMovementIntent
		const auto entity1 = registry.create();
		registry.emplace<Components::CameraMovementIntent>(entity1, Types::Vector2Float{10.0f, 5.0f});

		const auto entity2 = registry.create();
		registry.emplace<Components::CameraMovementIntent>(entity2, Types::Vector2Float{-3.0f, 2.0f});

		// Create and run the CameraMovementSystem
		Sample::Systems::Camera::CameraMovementSystem cameraMovementSystem{registry};
		cameraMovementSystem.Update();

		// Check if the camera center has moved according to the sum of intents
		const auto &renderSettings = ctx.get<Components::RenderSettings>();
		EXPECT_EQ(renderSettings.cameraCenter.x, 7.0f);
		EXPECT_EQ(renderSettings.cameraCenter.y, 7.0f);
	}
}
