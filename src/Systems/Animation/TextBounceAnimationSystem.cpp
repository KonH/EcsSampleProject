#include "TextBounceAnimationSystem.h"

#include <string>

#include <tweeny.h>

#include "Components/ActionFinish.h"
#include "Components/ActionProgress.h"
#include "Components/ActionStart.h"

#include "Components/Render/Text.h"

#include "Components/Presentation/NeedBounceAnimation.h"

#include "Components/Animation/TextBounceAnimation.h"

namespace Sample::Systems::Animation {
	using namespace Sample::Components;
	using namespace Sample::Components::Render;
	using namespace Sample::Components::Presentation;
	using namespace Sample::Components::Animation;

	TextBounceAnimationSystem::TextBounceAnimationSystem(entt::registry& registry) : _registry(registry) {}

	void TextBounceAnimationSystem::Update() {
		constexpr auto easing = tweeny::easing::bounceOut;

		auto startView = _registry.view<Text, NeedBounceAnimation>(entt::exclude<TextBounceAnimation>);
		for (auto&& [entity, text]: startView.each()) {
			const auto tween = tweeny::from(1.0f).to(1.1f).during(330).via(easing);
			_registry.emplace<TextBounceAnimation>(entity, tween, text.size);
			_registry.emplace<ActionProgress>(entity, 0.0f, 0.33f);
			_registry.remove<NeedBounceAnimation>(entity);
		}

		auto commonView = _registry.view<Text, TextBounceAnimation, ActionProgress>();
		for (auto&& [entity, text, anim, progress]: commonView.each()) {
			const auto p = progress.progress / progress.duration;
			const auto value = anim.tween.seek(p);
			text.size = value * anim.baseTextSize;
		}

		auto finishView = _registry.view<Text, TextBounceAnimation, ActionFinish>();
		for (auto&& [entity, text, anim]: finishView.each()) {
			text.size = anim.baseTextSize;
			_registry.remove<TextBounceAnimation>(entity);
		}
	}
}

