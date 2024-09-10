#pragma once

#include <entt/entity/registry.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "System.h"

namespace Sample::Systems {
	class AppWindowInitSystem final : public System {
	public:
		explicit AppWindowInitSystem(entt::registry& registry);

		void Init() override;

	private:
		entt::registry& _registry;
	};
}
