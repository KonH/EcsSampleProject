#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
	class HighlightCellByMousePositionSystem final : public System {
	public:
		explicit HighlightCellByMousePositionSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}