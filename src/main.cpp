#include <entt/entt.hpp>

#include "Common/ResourceConstants.h"

#include "Types/Color.h"
#include "Types/Vector2Float.h"

#include "Components/RenderColor.h"
#include "Components/RenderFill.h"
#include "Components/RenderLine.h"
#include "Components/Text.h"
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
#include "Components/NextTurnButton.h"
#include "Components/ResourceCounter.h"
#include "Components/HasOwner.h"
#include "Components/ResourceHolder.h"
#include "Components/BoxCollider.h"
#include "Components/Button.h"
#include "Components/Building.h"
#include "Components/Province.h"

#include "Configs/BuildingConfig.h"
#include "Configs/BuildingConfigProvider.h"

#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include "Logging/Logger.h"

#include "Systems/SystemsBuilder.h"

// TODO - add UI toolset
// TODO - add serialization

int main() {
	using namespace Sample::Types;
	using namespace Sample::Components;
	using namespace Sample::Configs;

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

	const auto buildingId = "TownHall";

	std::map<std::string, BuildingConfig> buildingConfigs;
	buildingConfigs[buildingId] = BuildingConfig {
		buildingId,
		{
			{ "Coins", Sample::ResourceConstants::GetResourceUnits(0.5f) }
		}
	};
	ctx.emplace<BuildingConfigProvider>(buildingConfigs);

	const auto locationRenderLayer = 0;
	const auto unitRenderLayer = 1;
	const auto highlightRenderLayer = 2;
	const auto uiAssetRenderLayer = 10;
	const auto uiTextRenderLayer = 11;

	const auto turnsResourceId = Sample::ResourceConstants::TURNS_RESOURCE_ID;
	const auto coinsResourceId = "Coins";

	const auto globalEntity = registry.create();
	std::map<std::string, long> globalResources;
	globalResources[turnsResourceId] = Sample::ResourceConstants::GetResourceUnits(1);
	registry.emplace<ResourceHolder>(globalEntity, globalResources);

	const auto playerEntity = registry.create();
	registry.emplace<IsPlayer>(playerEntity);
	std::map<std::string, long> playerResources;
	playerResources[coinsResourceId] = Sample::ResourceConstants::GetResourceUnits(10);
	registry.emplace<ResourceHolder>(playerEntity, playerResources);

	{
		const auto playerProvince = registry.create();
		registry.emplace<Province>(playerProvince);
		registry.emplace<WorldPosition>(playerProvince, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(playerProvince);
		registry.emplace<RenderPosition>(playerProvince);
		registry.emplace<RenderColor>(playerProvince, Color { 0, 0, 255, 255 });
		registry.emplace<RenderFill>(playerProvince);
		registry.emplace<RenderLayer>(playerProvince, locationRenderLayer);
		registry.emplace<HasOwner>(playerProvince, playerEntity);

		const auto buildingEntity = registry.create();
		registry.emplace<Building>(buildingEntity, "TownHall");
		registry.emplace<HasOwner>(buildingEntity, playerProvince);
	}

	{
		const auto playerArmy = registry.create();
		registry.emplace<WorldPosition>(playerArmy, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(playerArmy);
		registry.emplace<RenderPosition>(playerArmy);
		registry.emplace<RenderColor>(playerArmy, Color { 0, 155, 0, 255 });
		registry.emplace<RenderFill>(playerArmy);
		registry.emplace<RenderScale>(playerArmy, 0.5f);
		registry.emplace<RenderLayer>(playerArmy, unitRenderLayer);
		registry.emplace<Army>(playerArmy);
		registry.emplace<IsPlayer>(playerArmy);
		registry.emplace<HighlightColor>(playerArmy, Color { 0, 255, 0, 255 },  Color { 0, 155, 0, 255 });
	}

	{
		const auto otherProvince = registry.create();
		registry.emplace<Province>(otherProvince);
		registry.emplace<WorldPosition>(otherProvince, -1.0f, 0.0f);
		registry.emplace<ScreenPosition>(otherProvince);
		registry.emplace<RenderPosition>(otherProvince);
		registry.emplace<RenderColor>(otherProvince, Color { 255, 0, 0, 255 });
		registry.emplace<RenderFill>(otherProvince);
		registry.emplace<RenderLayer>(otherProvince, locationRenderLayer);
	}

	{
		const auto cellHighlighter = registry.create();
		registry.emplace<WorldPosition>(cellHighlighter, 0.0f, 0.0f);
		registry.emplace<ScreenPosition>(cellHighlighter);
		registry.emplace<RenderPosition>(cellHighlighter);
		registry.emplace<RenderColor>(cellHighlighter, Color { 125, 125, 125, 125 });
		registry.emplace<RenderFill>(cellHighlighter);
		registry.emplace<RenderScale>(cellHighlighter, 0.75f);
		registry.emplace<RenderLayer>(cellHighlighter, highlightRenderLayer);
		registry.emplace<IsHighlightCell>(cellHighlighter);
	}

	{
		const auto offset = 20;
		const auto width = 120;
		const auto height = 60;

		const auto nextTurnButtonBorder = registry.create();
		std::vector<Vector2Int> positions;
		positions.push_back(Vector2Int { screenWidth - width - offset, screenHeight - height - offset });
		positions.push_back(Vector2Int { screenWidth - offset, screenHeight - height - offset });
		positions.push_back(Vector2Int { screenWidth - offset, screenHeight - offset });
		positions.push_back(Vector2Int { screenWidth - width - offset, screenHeight - offset });
		positions.push_back(Vector2Int { screenWidth - width - offset, screenHeight - height - offset });
		registry.emplace<ScreenPositionSet>(nextTurnButtonBorder, positions);
		registry.emplace<RenderPositionSet>(nextTurnButtonBorder);
		registry.emplace<RenderLine>(nextTurnButtonBorder);
		registry.emplace<RenderColor>(nextTurnButtonBorder, Color { 0, 125, 0, 255 });
		registry.emplace<RenderLayer>(nextTurnButtonBorder, uiAssetRenderLayer);

		const auto textOffset = 10;

		const auto nextTurnButtonText = registry.create();
		registry.emplace<ScreenPosition>(nextTurnButtonText, screenWidth - width - offset + textOffset, screenHeight - height - offset + textOffset);
		registry.emplace<RenderPosition>(nextTurnButtonText);
		registry.emplace<Text>(nextTurnButtonText, "Roboto-Black.ttf", 22, "Next Turn");
		registry.emplace<RenderColor>(nextTurnButtonText, Color { 0, 125, 0, 255 });
		registry.emplace<RenderLayer>(nextTurnButtonText, uiTextRenderLayer);

		const auto nextTurnButton = registry.create();
		registry.emplace<ScreenPosition>(nextTurnButton, screenWidth - width - offset, screenHeight - height - offset);
		registry.emplace<BoxCollider>(nextTurnButton, Vector2Int { width, height });
		registry.emplace<Button>(nextTurnButton);
		registry.emplace<NextTurnButton>(nextTurnButton);
	}

	{
        const auto turnsCounterText = registry.create();
        registry.emplace<ScreenPosition>(turnsCounterText, screenWidth - 120, 20);
        registry.emplace<RenderPosition>(turnsCounterText);
        registry.emplace<Text>(turnsCounterText, "Roboto-Black.ttf", 25, "Turns: 0");
		registry.emplace<RenderColor>(turnsCounterText, Color { 0, 125, 0, 255 });
        registry.emplace<RenderLayer>(turnsCounterText, uiTextRenderLayer);
		registry.emplace<ResourceCounter>(turnsCounterText, turnsResourceId, globalEntity);
	}
	
	{
		const auto resourceCounterText = registry.create();
		registry.emplace<ScreenPosition>(resourceCounterText, 20, 20);
		registry.emplace<RenderPosition>(resourceCounterText);
		registry.emplace<Text>(resourceCounterText, "Roboto-Black.ttf", 25, "Coins: 0");
		registry.emplace<RenderColor>(resourceCounterText, Color { 0, 125, 0, 255 });
		registry.emplace<RenderLayer>(resourceCounterText, uiTextRenderLayer);
		registry.emplace<ResourceCounter>(resourceCounterText, coinsResourceId, playerEntity);
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
