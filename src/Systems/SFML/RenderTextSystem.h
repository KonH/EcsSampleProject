#pragma once
#ifdef USE_RENDER_SFML
#include <entt/entity/registry.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Systems/System.h"

namespace Sample::Systems::SFML {
	class RenderTextSystem final : public System {
	public:
		explicit RenderTextSystem(entt::registry& registry);

		void Update() override;

	private:
		std::shared_ptr<sf::Font> TryLoadFont(const std::string& fontName);

	private:
		entt::registry& _registry;
		std::unordered_map<std::string, std::shared_ptr<sf::Font>> _fontCache;
	};
}
#endif