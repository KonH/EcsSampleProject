#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/MouseScroll.h"
#include "Components/RenderSettings.h"

#include "Systems/Camera/CameraZoomSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleCameraZoomSystemTest, ZoomIn) {
		entt::registry registry;

		// Set up initial render settings
		auto &ctx = registry.ctx();
		ctx.emplace<Components::RenderSettings>("ECS Sample Project", // windowTitle
												1200u, // screenWidth
												800u, // screenHeight
												50.f, // unitSize
												Types::Vector2Float{0.0f, 0.0f} // cameraCenter
		);

		// Create an entity with MouseScroll for zooming in
		const auto entity = registry.create();
		registry.emplace<Components::MouseScroll>(entity, 1.0f);

		// Create and run the CameraZoomSystem
		Sample::Systems::Camera::CameraZoomSystem cameraZoomSystem{registry};
		cameraZoomSystem.Update();

		// Check if the unit size has increased
		const auto &renderSettings = ctx.get<Components::RenderSettings>();
		EXPECT_FLOAT_EQ(renderSettings.unitSize, 50.f * 1.1f);
	}

	TEST(EcsSampleCameraZoomSystemTest, ZoomOut) {
		entt::registry registry;

		// Set up initial render settings
		auto &ctx = registry.ctx();
		ctx.emplace<Components::RenderSettings>("ECS Sample Project", // windowTitle
												1200u, // screenWidth
												800u, // screenHeight
												50.f, // unitSize
												Types::Vector2Float{0.0f, 0.0f} // cameraCenter
		);

		// Create an entity with MouseScroll for zooming out
		const auto entity = registry.create();
		registry.emplace<Components::MouseScroll>(entity, -1.0f);

		// Create and run the CameraZoomSystem
		Sample::Systems::Camera::CameraZoomSystem cameraZoomSystem{registry};
		cameraZoomSystem.Update();

		// Check if the unit size has decreased
		const auto &renderSettings = ctx.get<Components::RenderSettings>();
		EXPECT_FLOAT_EQ(renderSettings.unitSize, 50.f / 1.1f);
	}
}
