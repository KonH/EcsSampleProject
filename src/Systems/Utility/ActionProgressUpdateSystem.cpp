#include "ActionProgressUpdateSystem.h"

#include "Components/Runtime.h"
#include "Components/ActionProgress.h"
#include "Components/ActionFinish.h"

namespace Sample::Systems::Utility {
	ActionProgressUpdateSystem::ActionProgressUpdateSystem(entt::registry &registry) : _registry(registry) {}

	void ActionProgressUpdateSystem::Update() {
		const auto deltaTime = _registry.ctx().get<Components::Runtime>().deltaTime;
		const auto view = _registry.view<Components::ActionProgress>();
		for (auto [entity, progress] : view.each()) {
			progress.progress += deltaTime;
			if (progress.progress >= progress.duration) {
				_registry.emplace<Components::ActionFinish>(entity);
			}
		}
	}
}