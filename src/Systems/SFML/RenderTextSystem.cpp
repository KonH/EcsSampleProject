#ifdef USE_RENDER_SFML
#include "RenderTextSystem.h"

#include <cassert>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Utils.h"
#include "Components/SFML/AppWindow.h"
#include "Components/ScreenPosition.h"
#include "Components/RenderColor.h"
#include "Components/Text.h"
#include "Logging/Logger.h"

namespace Sample::Systems::SFML {
	RenderTextSystem::RenderTextSystem(entt::registry &registry) : _registry(registry) {}

	void RenderTextSystem::Update() {
		assert(_registry.ctx().contains<Components::SFML::AppWindow>() && "AppWindow singleton not found!");
		auto& appWindow = _registry.ctx().get<Components::SFML::AppWindow>();
		auto& window = appWindow.window;

		const auto& view = _registry.view<Components::ScreenPosition, Components::RenderColor, Components::Text>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::ScreenPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);
			const auto& text = view.get<Components::Text>(entity);

			if (const auto font = TryLoadFont(text.fontName); font) {
				auto t = sf::Text(*font);
				t.setString(text.text);
				t.setCharacterSize(text.size);
				t.setFillColor(Utils::ConvertColor(renderColor.color));
				t.setPosition(sf::Vector2f(static_cast<float>(position.x), static_cast<float>(position.y)));

				window.draw(t);
			}
		}
	}

	std::shared_ptr<sf::Font> RenderTextSystem::TryLoadFont(const std::string& fontName) {
		if (_fontCache.contains(fontName)) {
			return _fontCache[fontName];
		}
		const auto fontPath = "../assets/fonts/" + fontName;
		const auto fontOpt = sf::Font::openFromFile(fontPath);
		if (!fontOpt.has_value()) {
			_fontCache[fontName] = nullptr;
			Logging::Logger::LogError("Failed to load font: " + fontPath);
			return nullptr;
		}
		_fontCache[fontName] = std::make_shared<sf::Font>(fontOpt.value());
		return _fontCache[fontName];
	}
}
#endif