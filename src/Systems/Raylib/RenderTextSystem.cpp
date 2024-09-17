#ifdef USE_RENDER_RAYLIB
#include "RenderTextSystem.h"

#include <raylib.h>

#include "Components/ScreenPosition.h"
#include "Components/RenderColor.h"
#include "Components/Text.h"
#include "Logging/Logger.h"

namespace Sample::Systems::Raylib {
	RenderTextSystem::RenderTextSystem(entt::registry &registry) : _registry(registry) {}

	void RenderTextSystem::Update() {
		const auto& view = _registry.view<Components::ScreenPosition, Components::RenderColor, Components::Text>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::ScreenPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);
			const auto& text = view.get<Components::Text>(entity);

			if (const auto font = TryLoadFont(text.fontName); font) {
				DrawTextEx(*font, text.text.c_str(), Vector2{ static_cast<float>(position.x), static_cast<float>(position.y) }, text.size, 1, Color{ renderColor.color.red, renderColor.color.green, renderColor.color.blue, renderColor.color.alpha });
			}
		}
	}

	std::shared_ptr<Font> RenderTextSystem::TryLoadFont(const std::string& fontName) {
		if (_fontCache.contains(fontName)) {
			return _fontCache[fontName];
		}
		const auto fontPath = "../assets/fonts/" + fontName;
		Font font = LoadFont(fontPath.c_str());
		if (!font.texture.id) {
			_fontCache[fontName] = nullptr;
			Logging::Logger::LogError("Failed to load font: " + fontPath);
			return nullptr;
		}
		_fontCache[fontName] = std::make_shared<Font>(font);
		return _fontCache[fontName];
	}
}
#endif