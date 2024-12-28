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
#include "Components/IsHighlightCell.h"
#include "Components/Army.h"
#include "Components/IsPlayer.h"
#include "Components/HighlightColor.h"

#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include "Logging/Logger.h"

#include "Systems/SystemsBuilder.h"

// TODO - add serialization

int main() {
	using namespace Sample::Types;
	using namespace Sample::Components;

	Sample::Logging::Logger::LogInfo("Starting ECS Sample Project");
	
	const auto screenWidth = 1200;
	const auto screenHeight = 800;

	entt::registry registry;
	std::vector<std::unique_ptr<Sample::Systems::System>> systems;
	auto& ctx = registry.ctx();
	ctx.emplace<RenderSettings>(
		"ECS Sample Project", // windowTitle
		static_cast<unsigned int>(screenWidth),
		static_cast<unsigned int>(screenHeight),
		50.f, // unitSize
		Vector2Float { 0.0f, 0.0f } // cameraCenter
	);
	ctx.emplace<Runtime>(
		true, // isRunning
		0.f // deltaTime
	);

	const auto locationRenderLayer = 0;
	const auto unitRenderLayer = 1;
	const auto highlightRenderLayer = 2;

	{
		const auto playerProvince = registry.create();
		registry.emplace<WorldPosition>(playerProvince, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(playerProvince);
		registry.emplace<RenderPosition>(playerProvince);
		registry.emplace<RenderColor>(playerProvince, Color { 0, 0, 255, 255 });
		registry.emplace<RenderLayer>(playerProvince, locationRenderLayer);
		registry.emplace<HasOwner>(playerProvince, player);
	}

	{
		const auto playerArmy = registry.create();
		registry.emplace<WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(playerArmy);
		registry.emplace<RenderPosition>(playerArmy);
		registry.emplace<RenderColor>(playerArmy, Color { 0, 155, 0, 255 });
		registry.emplace<RenderScale>(playerArmy, 0.5f);
		registry.emplace<RenderLayer>(playerArmy, unitRenderLayer);
		registry.emplace<Army>(playerArmy);
		registry.emplace<IsPlayer>(playerArmy);
		registry.emplace<HighlightColor>(playerArmy, Color { 0, 255, 0, 255 },  Color { 0, 155, 0, 255 });
	}

	{
		const auto otherProvince = registry.create();
		registry.emplace<WorldPosition>(otherProvince, -1.0f, 0.0f);
		registry.emplace<ScreenPosition>(otherProvince);
		registry.emplace<RenderPosition>(otherProvince);
		registry.emplace<RenderColor>(otherProvince, Color { 255, 0, 0, 255 });
		registry.emplace<RenderLayer>(otherProvince, locationRenderLayer);
	}

	{
		const auto cellHighlighter = registry.create();
		registry.emplace<WorldPosition>(cellHighlighter, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(cellHighlighter);
		registry.emplace<RenderPosition>(cellHighlighter);
		registry.emplace<RenderColor>(cellHighlighter, Color { 125, 125, 125, 125 });
		registry.emplace<RenderScale>(cellHighlighter, 0.75f);
		registry.emplace<RenderLayer>(cellHighlighter, highlightRenderLayer);
		registry.emplace<IsHighlightCell>(cellHighlighter);
	}
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
