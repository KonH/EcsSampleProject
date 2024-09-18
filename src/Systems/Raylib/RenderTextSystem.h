#pragma once
#ifdef USE_RENDER_RAYLIB

#include <string>
#include <unordered_map>

#include <raylib.h>
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class RenderTextSystem final : public System {
	public:
		explicit RenderTextSystem(entt::registry& registry);

		void Update() override;

	private:
		std::shared_ptr<Font> TryLoadFont(const std::string& fontName);

	private:
		entt::registry& _registry;
		std::unordered_map<std::string, std::shared_ptr<Font>> _fontCache;
	};
}
#endif