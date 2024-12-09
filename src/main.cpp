#include <entt/entt.hpp>

#include "Types/Color.h"
#include "Types/Vector2Float.h"
#include "Components/RenderColor.h"
#include "Components/RenderLine.h"
#include "Components/RenderPosition.h"
#include "Components/RenderPositionSet.h"
#include "Components/RenderSettings.h"
#include "Components/Runtime.h"
#include "Components/ScreenPosition.h"
#include "Components/ScreenPositionSet.h"
#include "Components/WorldPosition.h"
#include "Components/WorldPositionSet.h"
#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include "Logging/Logger.h"
#include "Systems/Animation/MovementAnimationSystem.h"
#include "Systems/Movement/WorldMovementSystem.h"
#include "Systems/Presentation/WorldToScreenPositionSystem.h"
#include "Systems/Presentation/WorldToScreenPositionSetSystem.h"
#include "Systems/Presentation/ScreenToRenderPositionSystem.h"
#include "Systems/Presentation/ScreenToRenderPositionSetSystem.h"
#include "Systems/Utility/ActionProgressCleanUpSystem.h"
#include "Systems/Utility/ActionProgressUpdateSystem.h"
#include "Systems/Utility/DeltaTimeUpdateSystem.h"
#include "Systems/Utility/EventCleanUpSystem.h"
#include "Systems/Camera/CameraZoomSystem.h"
#include "Systems/Camera/CameraMovementIntentSystem.h"
#include "Systems/Camera/CameraMovementSystem.h"

// TODO - add serialization

int main() {
	Sample::Logging::Logger::LogInfo("Starting ECS Sample Project");
	entt::registry registry;
	std::vector<std::unique_ptr<Sample::Systems::System>> systems;
	auto& ctx = registry.ctx();
	ctx.emplace<Sample::Components::RenderSettings>(
		"ECS Sample Project", // windowTitle
		static_cast<unsigned int>(1200), // screenWidth
		static_cast<unsigned int>(800), // screenHeight
		50.f, // unitSize
		Sample::Types::Vector2Float { 0.0f, 0.0f } // cameraCenter
	);
	ctx.emplace<Sample::Components::Runtime>(
		true, // isRunning
		0.f // deltaTime
	);

	{
		const auto playerProvince = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerProvince, 0.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(playerProvince);
		registry.emplace<Sample::Components::RenderPosition>(playerProvince);
		registry.emplace<Sample::Components::RenderColor>(playerProvince, Sample::Types::Color { 0, 0, 255, 255 });
	}

	{
		const auto playerUnit = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerUnit, 0.0f, 1.0f);
		registry.emplace<Sample::Components::ScreenPosition>(playerUnit);
		registry.emplace<Sample::Components::RenderPosition>(playerUnit);
		registry.emplace<Sample::Components::RenderColor>(playerUnit, Sample::Types::Color { 0, 255, 0, 255 });
	}

	{
		const auto otherProvince = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(otherProvince, -1.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(otherProvince);
		registry.emplace<Sample::Components::RenderPosition>(otherProvince);
		registry.emplace<Sample::Components::RenderColor>(otherProvince, Sample::Types::Color { 255, 0, 0, 255 });
	}

	// TODO: simplify this
	systems.push_back(std::make_unique<Sample::Systems::Utility::DeltaTimeUpdateSystem>(registry));
	Sample::Frontend::FrontendSystems::PreMainInitialize(registry, systems);
	systems.push_back(std::make_unique<Sample::Systems::Utility::ActionProgressUpdateSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Movement::WorldMovementSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::WorldToScreenPositionSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::WorldToScreenPositionSetSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Animation::MovementAnimationSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::ScreenToRenderPositionSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Presentation::ScreenToRenderPositionSetSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Camera::CameraZoomSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Camera::CameraMovementIntentSystem>(registry));
	systems.push_back(std::make_unique<Sample::Systems::Camera::CameraMovementSystem>(registry));
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
