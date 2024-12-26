#pragma once

#include <entt/entt.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "Systems/System.h"
#include "Systems/SystemsBuilder.h"

namespace Sample::Tests {
	TEST(EcsSampleSystemsBuilderTest, PreMainInitializeCreatesSystems) {
		entt::registry registry;
		std::vector<std::unique_ptr<Systems::System>> systems;

		Sample::Systems::SystemsBuilder::PreMainInitialize(registry, systems);

		EXPECT_FALSE(systems.empty());
	}

	TEST(EcsSampleSystemsBuilderTest, MainInitializeCreatesSystems) {
		entt::registry registry;
		std::vector<std::unique_ptr<Systems::System>> systems;

		Sample::Systems::SystemsBuilder::MainInitialize(registry, systems);

		EXPECT_FALSE(systems.empty());
	}

	TEST(EcsSampleSystemsBuilderTest, PostMainInitializeCreatesSystems) {
		entt::registry registry;
		std::vector<std::unique_ptr<Systems::System>> systems;

		Sample::Systems::SystemsBuilder::PostMainInitialize(registry, systems);

		EXPECT_FALSE(systems.empty());
	}
}
