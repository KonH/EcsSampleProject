#include <entt/entt.hpp>

#include "Components/IsPlayer.h"
#include "Components/RenderColor.h"
#include "Components/RenderSettings.h"
#include "Components/Runtime.h"
#include "Components/ScreenPosition.h"
#include "Components/WorldPosition.h"
#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include "Logging/Logger.h"
#include "Systems/Movement/PlayerMovementSystem.h"
#include "Systems/Movement/WorldMovementSystem.h"
#include "Systems/Presentation/WorldToScreenPositionSystem.h"
#include "Systems/Utility/EventCleanUpSystem.h"

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
		true // isRunning
	);

	{
		const auto playerEntity = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerEntity, 0, 0);
		registry.emplace<Sample::Components::ScreenPosition>(playerEntity, 0, 0);
		registry.emplace<Sample::Components::RenderColor>(playerEntity, Sample::Types::Color { 0, 255, 0, 255 });
		registry.emplace<Sample::Components::IsPlayer>(playerEntity);
	}

	Sample::Frontend::FrontendSystems::PreMainInitialize(registry, systems);
	systems.push_back(std::make_unique<Sample::Systems::Movement::PlayerMovementSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Movement::WorldMovementSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::WorldToScreenPositionSystem>(registry));
	Sample::Frontend::FrontendSystems::PostMainInitialize(registry, systems);
	systems.push_back(std::make_unique<Sample::Systems::Utility::EventCleanUpSystem>(registry));

	for (const auto& system : systems) {
		system->Init();
	}

	Sample::Execution::MainLoopRunner mainLoopRunner(registry, systems);
	mainLoopRunner.Run();

	return 0;
}
