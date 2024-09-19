#pragma once
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Utility {
	class EventCleanUpSystem final : public System {
	public:
		explicit EventCleanUpSystem(entt::registry& registry);

		void Update() override;

	private:
		template<class T>
		void CleanUp() {
			_registry.view<T>().each([this](const entt::entity entity, auto) {
				_registry.remove<T>(entity);
				if (_registry.orphan(entity)) {
					_registry.destroy(entity);
				}
			});
		}

	private:
		entt::registry& _registry;
	};
}