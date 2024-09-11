#include <entt/entt.hpp>

#include "Components/RenderSettings.h"
#include "Components/Runtime.h"

#include "Components/Position.h"
#include "Components/RenderColor.h"

#include "Systems/System.h"

#ifdef USE_RENDER_SFML
#include "Systems/SFML/AppWindowInitSystem.h"
#include "Systems/SFML/InputSystem.h"
#include "Systems/SFML/RenderSystem.h"
#endif

#ifdef USE_RENDER_SDL
#include "Systems/SDL/AppWindowInitSystem.h"
#include "Systems/SDL/InputSystem.h"
#include "Systems/SDL/RenderSystem.h"
#endif

int main() {
	entt::registry registry;

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

	const auto testEntity = registry.create();
	registry.emplace<Sample::Components::Position>(testEntity, 0, 0);
	registry.emplace<Sample::Components::RenderColor>(testEntity, Sample::Types::Color { 0, 255, 0, 255 });

	std::vector<std::unique_ptr<Sample::Systems::System>> systems;

#ifdef USE_RENDER_SFML
	systems.emplace_back(std::make_unique<Sample::Systems::SFML::AppWindowInitSystem>(registry));
	systems.emplace_back(std::make_unique<Sample::Systems::SFML::InputSystem>(registry)); // InputSystem depends on AppWindowInitSystem
	systems.emplace_back(std::make_unique<Sample::Systems::SFML::RenderSystem>(registry)); // RenderSystem depends on AppWindowInitSystem
#endif

#if USE_RENDER_SDL
	systems.emplace_back(std::make_unique<Sample::Systems::SDL::AppWindowInitSystem>(registry));
	systems.emplace_back(std::make_unique<Sample::Systems::SDL::InputSystem>(registry)); // InputSystem depends on AppWindowInitSystem
	systems.emplace_back(std::make_unique<Sample::Systems::SDL::RenderSystem>(registry)); // RenderSystem depends on AppWindowInitSystem
#endif

	for (const auto& system : systems) {
		system->Init();
	}

	while (ctx.get<Sample::Components::Runtime>().isRunning) {
		for (const auto& system : systems) {
			system->Update();
		}
	}

	return 0;
}
