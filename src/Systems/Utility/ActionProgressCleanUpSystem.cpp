#include "ActionProgressCleanUpSystem.h"

#include "Components/ActionProgress.h"
#include "Components/ActionFinish.h"

namespace Sample::Systems::Utility {
	ActionProgressCleanUpSystem::ActionProgressCleanUpSystem(entt::registry &registry) : _registry(registry) {}

	void ActionProgressCleanUpSystem::Update() {
		const auto view = _registry.view<Components::ActionProgress, Components::ActionFinish>();
		for (auto [entity, progress] : view.each()) {
			_registry.remove<Components::ActionProgress>(entity);
			_registry.remove<Components::ActionFinish>(entity);
			if (_registry.orphan(entity)) {
				_registry.destroy(entity);
			}
		}
	}
}