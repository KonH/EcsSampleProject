#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Presentation {
	class HighlightSelectedSystem final : public System {
	public:
		explicit HighlightSelectedSystem(entt::registry& registry);

		void Update() override;

	private:
		entt::registry& _registry;
	};
}