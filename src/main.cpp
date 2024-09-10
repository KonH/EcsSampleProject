#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "Components/RenderSettings.h"
#include "Components/Runtime.h"

#include "Components/Position.h"
#include "Components/RenderColor.h"

#include "Systems/AppWindowInitSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/RenderSystem.h"

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
	registry.emplace<Sample::Components::RenderColor>(testEntity, sf::Color::Green);

	std::vector<std::unique_ptr<Sample::Systems::System>> systems;
	systems.emplace_back(std::make_unique<Sample::Systems::AppWindowInitSystem>(registry));
	systems.emplace_back(std::make_unique<Sample::Systems::InputSystem>(registry)); // InputSystem depends on AppWindowInitSystem
	systems.emplace_back(std::make_unique<Sample::Systems::RenderSystem>(registry)); // RenderSystem depends on AppWindowInitSystem

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
