#pragma once
#ifdef USE_RENDER_RAYLIB

#include <string>
#include <unordered_map>

#include <entt/entity/registry.hpp>
#include <raylib.h>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class RenderTextureSystem final : public System {
	public:
		explicit RenderTextureSystem(entt::registry& registry);

		void Update() override;

	private:
		std::shared_ptr<Texture2D> TryLoadTexture(const std::string& textureName);

	private:
		entt::registry& _registry;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> _textureCache;
	};
}
#endif