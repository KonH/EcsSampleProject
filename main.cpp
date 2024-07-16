#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

struct Position {
	float x;
	float y;
};

struct Velocity {
	float vx;
	float vy;
};

int main() {
	const auto& modelSize = sf::Vector2u(800, 600);
	sf::RenderWindow window(sf::VideoMode(modelSize), "EcsSampleProject");

	entt::registry registry;

	{
		const auto entity = registry.create();
		registry.emplace<Position>(entity, 400.f, 300.f);
		registry.emplace<Velocity>(entity, 0.001f, 0.001f);
	}

	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		while (auto eventOpt = window.pollEvent()) {
			if (eventOpt.has_value()) {
				const auto& event = eventOpt.value();
				if (event.is<sf::Event::Closed>()) {
					window.close();
				}
			}
		}

		auto view = registry.view<Position, Velocity>();
		for (const auto entity : view) {
			auto& pos = view.get<Position>(entity);
			const auto& vel = view.get<Velocity>(entity);
			pos.x += vel.vx;
			pos.y += vel.vy;
		}

		window.clear();
		for (const auto entity : view) {
			const auto& pos = view.get<Position>(entity);
			auto vector = sf::Vector2f(pos.x, pos.y);
			shape.setPosition(vector);
			window.draw(shape);
		}
		window.display();
	}

	return 0;
}
