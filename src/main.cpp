#include <entt/entt.hpp>

#include "Components/IsObstacle.h"
#include "Components/IsPlayer.h"
#include "Components/RenderColor.h"
#include "Components/RenderPosition.h"
#include "Components/RenderSettings.h"
#include "Components/Runtime.h"
#include "Components/ScreenPosition.h"
#include "Components/WorldPosition.h"
#include "Components/IsHighlightCell.h"
#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include "Logging/Logger.h"
#include "Systems/Animation/MovementAnimationSystem.h"
#include "Systems/Movement/PlayerMovementSystem.h"
#include <Systems/Movement/ObstacleFilterSystem.h>
#include "Systems/Movement/WorldMovementSystem.h"
#include "Systems/Presentation/ScreenToRenderPositionSystem.h"
#include "Systems/Presentation/WorldToScreenPositionSystem.h"
#include "Systems/Utility/ActionProgressCleanUpSystem.h"
#include "Systems/Utility/ActionProgressUpdateSystem.h"
#include "Systems/Utility/DeltaTimeUpdateSystem.h"
#include "Systems/Utility/EventCleanUpSystem.h"
#include "Systems/Camera/CameraZoomSystem.h"

// TODO - add serialization

void testAddObstacle(entt::registry& registry, const int x, const int y) {
	const auto obstacleEntity = registry.create();
	registry.emplace<Sample::Components::WorldPosition>(obstacleEntity, static_cast<float>(x), static_cast<float>(y));
	registry.emplace<Sample::Components::ScreenPosition>(obstacleEntity);
	registry.emplace<Sample::Components::RenderPosition>(obstacleEntity);
	registry.emplace<Sample::Components::RenderColor>(obstacleEntity, Sample::Types::Color { 255, 0, 0, 255 });
	registry.emplace<Sample::Components::IsObstacle>(obstacleEntity);
}

int main() {
	Sample::Logging::Logger::LogInfo("Starting ECS Sample Project");
	entt::registry registry;
	std::vector<std::unique_ptr<Sample::Systems::System>> systems;
	auto& ctx = registry.ctx();
	ctx.emplace<Sample::Components::RenderSettings>(
		"ECS Sample Project", // windowTitle
		static_cast<unsigned int>(800), // screenWidth
		static_cast<unsigned int>(600), // screenHeight
		50.f // unitSize
	);
	ctx.emplace<Sample::Components::Runtime>(
		true, // isRunning
		0.f // deltaTime
	);

	// * * * * *
	// * _ _ _ *
	// * * * _ *
	// * _ _ _ *
	// * _ P _ *
	// * _ _ _ *
	// * * * * *

	{
		const auto playerEntity = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerEntity, 0.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(playerEntity);
		registry.emplace<Sample::Components::RenderPosition>(playerEntity);
		registry.emplace<Sample::Components::RenderColor>(playerEntity, Sample::Types::Color { 0, 255, 0, 255 });
		registry.emplace<Sample::Components::IsPlayer>(playerEntity);
	}

	for (auto x = -2; x < 3; x++) {
		testAddObstacle(registry, x, -4);
		if (x != 1) {
			testAddObstacle(registry, x, -2);
		}
		testAddObstacle(registry, x, 2);
	}
	for (const auto y : { -3, -1, 0, 1 }) {
		testAddObstacle(registry, -2, y);
		testAddObstacle(registry, 2, y);
	}

	{
		const auto highlightCellEntity = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(highlightCellEntity, 0.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(highlightCellEntity);
		registry.emplace<Sample::Components::RenderPosition>(highlightCellEntity);
		registry.emplace<Sample::Components::RenderColor>(highlightCellEntity, Sample::Types::Color { 120, 120, 120, 120 });
		registry.emplace<Sample::Components::IsHighlightCell>(highlightCellEntity);
	}

	// TODO: simplify this
	systems.push_back(std::make_unique<Sample::Systems::Utility::DeltaTimeUpdateSystem>(registry));
	Sample::Frontend::FrontendSystems::PreMainInitialize(registry, systems);
	systems.push_back(std::make_unique<Sample::Systems::Utility::ActionProgressUpdateSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Movement::PlayerMovementSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Movement::ObstacleFilterSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Movement::WorldMovementSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::WorldToScreenPositionSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Animation::MovementAnimationSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::ScreenToRenderPositionSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Camera::CameraZoomSystem>(registry));
	Sample::Frontend::FrontendSystems::PostMainInitialize(registry, systems);
	systems.push_back(std::make_unique<Sample::Systems::Utility::ActionProgressCleanUpSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Utility::EventCleanUpSystem>(registry));

	for (const auto& system : systems) {
		system->Init();
	}

	Sample::Execution::MainLoopRunner mainLoopRunner(registry, systems);
	mainLoopRunner.Run();

	return 0;
}
