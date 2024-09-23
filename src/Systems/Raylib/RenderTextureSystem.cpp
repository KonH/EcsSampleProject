#ifdef USE_RENDER_RAYLIB
#include "RenderTextureSystem.h"

#include "Components/RenderPosition.h"
#include "Components/Texture.h"
#include "Logging/Logger.h"

namespace Sample::Systems::Raylib {
	RenderTextureSystem::RenderTextureSystem(entt::registry& registry) : _registry(registry) {}

	void RenderTextureSystem::Update() {
		const auto& view = _registry.view<Components::RenderPosition, Components::Texture>();
		for (const auto entity : view) {
			const auto& position = view.get<Components::RenderPosition>(entity);
			const auto& texture = view.get<Components::Texture>(entity);

			if (const auto t = TryLoadTexture(texture.textureName); t) {
				DrawTexture(*t, position.position.x, position.position.y, WHITE);
			}
		}
	}

	std::shared_ptr<Texture2D> RenderTextureSystem::TryLoadTexture(const std::string& textureName) {
		if (_textureCache.contains(textureName)) {
			return _textureCache[textureName];
		}
		const auto texturePath = "assets/textures/" + textureName;
		Texture2D texture = LoadTexture(texturePath.c_str());
		if (!texture.id) {
			_textureCache[textureName] = nullptr;
			Logging::Logger::LogError("Failed to load texture: " + texturePath);
			return nullptr;
		}
		_textureCache[textureName] = std::make_shared<Texture2D>(texture);
		return _textureCache[textureName];
	}
}
#endif