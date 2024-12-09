#include <entt/entt.hpp>

#include "Types/Color.h"
#include "Types/Vector2Float.h"
#include "Components/RenderColor.h"
#include "Components/RenderLine.h"
#include "Components/RenderPosition.h"
#include "Components/RenderScale.h"
#include "Components/RenderLayer.h"
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

#include "Systems/SystemsBuilder.h"

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

	const auto locationRenderLayer = 0;
	const auto unitRenderLayer = 1;

	{
		const auto playerProvince = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerProvince, 0.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(playerProvince);
		registry.emplace<Sample::Components::RenderPosition>(playerProvince);
		registry.emplace<Sample::Components::RenderColor>(playerProvince, Sample::Types::Color { 0, 0, 255, 255 });
		registry.emplace<Sample::Components::RenderLayer>(playerProvince, locationRenderLayer);
	}

	{
		const auto playerArmy = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(playerArmy);
		registry.emplace<Sample::Components::RenderPosition>(playerArmy);
		registry.emplace<Sample::Components::RenderColor>(playerArmy, Sample::Types::Color { 0, 255, 0, 255 });
		registry.emplace<Sample::Components::RenderScale>(playerArmy, 0.5f);
		registry.emplace<Sample::Components::RenderLayer>(playerArmy, unitRenderLayer);
	}

	{
		const auto otherProvince = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(otherProvince, -1.0f, 0.0f);
		registry.emplace<Sample::Components::ScreenPosition>(otherProvince);
		registry.emplace<Sample::Components::RenderPosition>(otherProvince);
		registry.emplace<Sample::Components::RenderColor>(otherProvince, Sample::Types::Color { 255, 0, 0, 255 });
		registry.emplace<Sample::Components::RenderLayer>(otherProvince, locationRenderLayer);
	}

	Sample::Systems::SystemsBuilder::PreMainInitialize(registry, systems);
	Sample::Frontend::FrontendSystems::PreMainInitialize(registry, systems);
	Sample::Systems::SystemsBuilder::MainInitialize(registry, systems);
	Sample::Frontend::FrontendSystems::PostMainInitialize(registry, systems);
	Sample::Systems::SystemsBuilder::PostMainInitialize(registry, systems);

	for (const auto& system : systems) {
		system->Init();
	}

	Sample::Execution::MainLoopRunner mainLoopRunner(registry, systems);
	mainLoopRunner.Run();

	return 0;
}
