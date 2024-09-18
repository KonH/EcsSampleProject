#include <entt/entt.hpp>

#include "Components/RenderSettings.h"
#include "Components/Runtime.h"
#include "Components/WorldPosition.h"
#include "Components/ScreenPosition.h"
#include "Components/RenderColor.h"
#include "Components/Text.h"
#include "Components/Texture.h"
#include "Execution/MainLoopRunner.h"
#include "Frontend/FrontendSystems.h"
#include <Logging/Logger.h>
#include "Systems/System.h"

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
		const auto testEntity = registry.create();
		registry.emplace<Sample::Components::WorldPosition>(testEntity, 0, 0);
		registry.emplace<Sample::Components::RenderColor>(testEntity, Sample::Types::Color { 0, 255, 0, 255 });
	}

	{
		const auto testLabel = registry.create();
		registry.emplace<Sample::Components::ScreenPosition>(testLabel, 0, 0);
		registry.emplace<Sample::Components::RenderColor>(testLabel, Sample::Types::Color { 255, 0, 0, 255 });
		registry.emplace<Sample::Components::Text>(testLabel, "Roboto-Regular.ttf", "Hello World!", 24);
	}

	{
		const auto testTexture = registry.create();
		registry.emplace<Sample::Components::ScreenPosition>(testTexture, 200, 0);
		registry.emplace<Sample::Components::Texture>(testTexture, "testTexture.png");
	}

	Sample::Frontend::FrontendSystems::Initialize(registry, systems);

	for (const auto& system : systems) {
		system->Init();
	}

	Sample::Execution::MainLoopRunner mainLoopRunner(registry, systems);
	mainLoopRunner.Run();

	return 0;
}
