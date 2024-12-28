#pragma once

#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::UI {
	class ButtonClickSystem final : public System {
	public:
		explicit ButtonClickSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}
