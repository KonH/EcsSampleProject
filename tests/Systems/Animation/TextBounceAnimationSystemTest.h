#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"
#include "Components/Animation/TextBounceAnimation.h"
#include "Components/Presentation/NeedBounceAnimation.h"
#include "Components/Render/Text.h"
#include "Systems/Animation/TextBounceAnimationSystem.h"

namespace Sample::Tests {
	TEST(EcsSampleTextBounceAnimationSystemTest, BounceAnimationStarts) {
		entt::registry registry;

		// Create an entity with Text and NeedBounceAnimation
		const auto entity = registry.create();
		registry.emplace<Sample::Components::Render::Text>(entity, "Roboto-Black.ttf", 25.0f, "Test Text");
		registry.emplace<Sample::Components::Presentation::NeedBounceAnimation>(entity);

		// Create and run the TextBounceAnimationSystem
		Sample::Systems::Animation::TextBounceAnimationSystem textBounceAnimationSystem{registry};
		textBounceAnimationSystem.Update();

		// Check if the TextBounceAnimation and ActionProgress components have been added
		ASSERT_TRUE(registry.all_of<Sample::Components::Animation::TextBounceAnimation>(entity));
		ASSERT_TRUE(registry.all_of<Sample::Components::ActionProgress>(entity));
		ASSERT_FALSE(registry.all_of<Sample::Components::Presentation::NeedBounceAnimation>(entity));
	}

	TEST(EcsSampleTextBounceAnimationSystemTest, BounceAnimationProgresses) {
		entt::registry registry;

		// Create an entity with Text and NeedBounceAnimation
		const auto entity = registry.create();
		registry.emplace<Sample::Components::Render::Text>(entity, "Roboto-Black.ttf", 25.0f, "Test Text");
		registry.emplace<Sample::Components::Presentation::NeedBounceAnimation>(entity);

		// Create and run the TextBounceAnimationSystem to start the animation
		Sample::Systems::Animation::TextBounceAnimationSystem textBounceAnimationSystem{registry};
		textBounceAnimationSystem.Update();

		// Simulate progress
		auto &progress = registry.get<Sample::Components::ActionProgress>(entity);
		progress.progress = 0.165f; // Halfway through the animation
		textBounceAnimationSystem.Update();

		// Check if the text size has been updated
		const auto &text = registry.get<Sample::Components::Render::Text>(entity);
		EXPECT_GT(text.size, 25.0f);
		EXPECT_LT(text.size, 27.5f); // Should be between the initial and final sizes
	}

	TEST(EcsSampleTextBounceAnimationSystemTest, BounceAnimationFinishes) {
		entt::registry registry;

		// Create an entity with Text and NeedBounceAnimation
		const auto entity = registry.create();
		registry.emplace<Sample::Components::Render::Text>(entity, "Roboto-Black.ttf", 25.0f, "Test Text");
		registry.emplace<Sample::Components::Presentation::NeedBounceAnimation>(entity);

		// Create and run the TextBounceAnimationSystem to start the animation
		Sample::Systems::Animation::TextBounceAnimationSystem textBounceAnimationSystem{registry};
		textBounceAnimationSystem.Update();

		// Simulate progress to the end of the animation
		auto &progress = registry.get<Sample::Components::ActionProgress>(entity);
		progress.progress = 0.33f; // End of the animation
		textBounceAnimationSystem.Update();

		// Add ActionFinish component to signal the end of the animation
		registry.emplace<Sample::Components::ActionFinish>(entity);
		textBounceAnimationSystem.Update();

		// Check if the TextBounceAnimation component has been removed and text size is reset
		ASSERT_FALSE(registry.all_of<Sample::Components::Animation::TextBounceAnimation>(entity));
		const auto &text = registry.get<Sample::Components::Render::Text>(entity);
		EXPECT_EQ(text.size, 25.0f);
	}
}
