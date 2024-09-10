#include "InputSystem.h"

#include <cassert>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "Components/AppWindow.h"
#include "Components/Runtime.h"

namespace Sample::Systems {
	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {}

	void InputSystem::Update() {
		assert(_registry.ctx().contains<Components::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::AppWindow>();
		auto& window = appWindow.window;

		while (auto eventOpt = window.pollEvent()) {
			if (eventOpt.has_value()) {
				const auto& event = eventOpt.value();
				if (event.is<sf::Event::Closed>()) {
					_registry.ctx().get<Components::Runtime>().isRunning = false;
					window.close();
				}
			}
		}
	}
}