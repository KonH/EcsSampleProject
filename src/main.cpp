#include <entt/entt.hpp>

#include "Components/RenderSettings.h"
#include "Components/Runtime.h"

#include "Components/Position.h"
#include "Components/RenderColor.h"

#include "Systems/System.h"

// TODO: refactor define usage

#ifdef USE_RENDER_SFML
#include "Systems/SFML/AppWindowInitSystem.h"
#include "Systems/SFML/InputSystem.h"
#include "Systems/SFML/RenderSystem.h"
#endif

#ifdef USE_RENDER_SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Systems/SDL/AppWindowInitSystem.h"
#include "Systems/SDL/InputSystem.h"
#include "Systems/SDL/RenderSystem.h"
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// TODO: refactor to runner class

// TODO: refactor logs

entt::registry registry;
std::vector<std::unique_ptr<Sample::Systems::System>> systems;

void MainLoop() {
	for (const auto& system : systems) {
		system->Update();
	}
#ifdef __EMSCRIPTEN__
	auto& ctx = registry.ctx();
	if (!ctx.get<Sample::Components::Runtime>().isRunning) {
		emscripten_cancel_main_loop();
	}
#endif
}

int main() {
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

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(MainLoop, 0, 1);
#else
	while (ctx.get<Sample::Components::Runtime>().isRunning) {
		MainLoop();
	}
#endif

	return 0;
}
