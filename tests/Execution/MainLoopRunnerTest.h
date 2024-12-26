#pragma once

#include <atomic>
#include <chrono>
#include <entt/entt.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <vector>

#include "Components/Runtime.h"
#include "Execution/MainLoopRunner.h"
#include "Systems/System.h"

namespace Sample::Tests {
	class MockSystem : public Systems::System {
	public:
		void Update() override { updateCalled = true; }

		std::atomic<bool> updateCalled{false};
	};

	TEST(EcsSampleMainLoopRunnerTest, SystemsUpdateCalled) {
		entt::registry registry;
		registry.ctx().emplace<Components::Runtime>().isRunning = true;

		auto mockSystem = std::make_unique<MockSystem>();
		auto mockSystemPtr = mockSystem.get();

		std::vector<std::unique_ptr<Systems::System>> systems;
		systems.push_back(std::move(mockSystem));

		Sample::Execution::MainLoopRunner runner(registry, systems);

		std::thread runnerThread([&runner]() { runner.Run(); });

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		registry.ctx().get<Components::Runtime>().isRunning = false;
		runnerThread.join();

		EXPECT_TRUE(mockSystemPtr->updateCalled);
	}

	TEST(EcsSampleMainLoopRunnerTest, MainLoopStopsWhenRuntimeIsNotRunning) {
		entt::registry registry;
		registry.ctx().emplace<Components::Runtime>().isRunning = true;

		auto mockSystem = std::make_unique<MockSystem>();
		auto mockSystemPtr = mockSystem.get();

		std::vector<std::unique_ptr<Systems::System>> systems;
		systems.push_back(std::move(mockSystem));

		Sample::Execution::MainLoopRunner runner(registry, systems);

		std::thread runnerThread([&runner]() { runner.Run(); });

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		registry.ctx().get<Components::Runtime>().isRunning = false;
		runnerThread.join();

		EXPECT_FALSE(registry.ctx().get<Components::Runtime>().isRunning);
		EXPECT_TRUE(mockSystemPtr->updateCalled);
	}
}
