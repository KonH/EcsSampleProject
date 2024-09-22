#ifdef USE_RENDER_RAYLIB
#include "RenderTextSystem.h"

#include <raylib.h>

#include "Components/ScreenPosition.h"
#include "Components/RenderColor.h"
#include "Components/Text.h"
#include "Logging/Logger.h"
#include "Utils.h"

namespace Sample::Systems::Raylib {
	RenderTextSystem::RenderTextSystem(entt::registry &registry) : _registry(registry) {}

	void RenderTextSystem::Update() {
		const auto& view = _registry.view<Components::ScreenPosition, Components::RenderColor, Components::Text>();
		for (const auto entity : view) {
			const auto& screenPosition = view.get<Components::ScreenPosition>(entity);
			const auto& renderColor = view.get<Components::RenderColor>(entity);
			const auto& text = view.get<Components::Text>(entity);

			if (const auto font = TryLoadFont(text.fontName); font) {
				const auto pos = Vector2 { static_cast<float>(screenPosition.x), static_cast<float>(screenPosition.y) };
				const auto color = Utils::ConvertColor(renderColor.color);
				DrawTextEx(*font, text.text.c_str(), pos, static_cast<float>(text.size), 1, color);
			}
		}
	}

	std::shared_ptr<Font> RenderTextSystem::TryLoadFont(const std::string& fontName) {
		if (_fontCache.contains(fontName)) {
			return _fontCache[fontName];
		}
		const auto fontPath = "assets/fonts/" + fontName;
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