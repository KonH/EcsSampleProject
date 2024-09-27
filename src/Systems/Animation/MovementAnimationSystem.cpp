#include "MovementAnimationSystem.h"

#include <string>

#include <tweeny.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"
#include "Components/RenderSettings.h"
#include "Components/ScreenOffset.h"
#include "Components/WorldMovement.h"
#include "Components/WorldMovementAnimation.h"
#include "Components/WorldPosition.h"

namespace Sample::Systems::Animation {
	MovementAnimationSystem::MovementAnimationSystem(entt::registry &registry) : _registry(registry) {}

	void MovementAnimationSystem::Update() {
		constexpr auto easing = tweeny::easing::bounceOut;
		const auto unitSize = _registry.ctx().get<Components::RenderSettings>().unitSize;
		const auto startView = _registry.view<Components::WorldPosition, Components::WorldMovement, Components::ActionProgress, Components::ActionStart>();
		for (auto [entity, position, movement, progress] : startView.each()) {
			const auto finalX = static_cast<float>(movement.change.x) * unitSize;
			const auto finalY = static_cast<float>(movement.change.y) * unitSize;
			const auto tween = tweeny::from(0.0f, 0.0f)
				.to(finalX, finalY).during(progress.duration * 1000).via(easing);
			_registry.emplace<Components::WorldMovementAnimation>(entity, tween);
			_registry.emplace<Components::ScreenOffset>(entity, 0, 0);
		}
		const auto commonView = _registry.view<Components::WorldMovementAnimation, Components::ActionProgress, Components::ScreenOffset>();
		for (auto [entity, anim, progress, offset] : commonView.each()) {
			const auto p = progress.progress / progress.duration;
			const auto value = anim.tween.seek(p);
			offset.offset.x = static_cast<int>(value[0]);
			offset.offset.y = static_cast<int>(value[1]);
		}
		const auto finishView = _registry.view<Components::WorldMovementAnimation, Components::ActionFinish>();
		for (auto tuple : finishView.each()) {
			const auto entity = std::get<0>(tuple);
			_registry.remove<Components::WorldMovementAnimation>(entity);
			_registry.remove<Components::ScreenOffset>(entity);
		}
	}
}