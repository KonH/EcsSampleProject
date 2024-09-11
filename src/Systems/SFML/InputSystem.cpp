#ifdef USE_RENDER_SFML
#include "InputSystem.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>

#include "Components/Runtime.h"
#include "Components/SFML/AppWindow.h"

namespace Sample::Systems::SFML {
	InputSystem::InputSystem(entt::registry &registry) : _registry(registry) {}

	void InputSystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
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
#endif