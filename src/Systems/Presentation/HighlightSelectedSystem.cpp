#include "HighlightSelectedSystem.h"

#include "Components/RenderColor.h"
#include "Components/HighlightColor.h"
#include "Components/IsSelected.h"

namespace Sample::Systems::Presentation {
	HighlightSelectedSystem::HighlightSelectedSystem(entt::registry& registry) : _registry(registry) {}

	void HighlightSelectedSystem::Update() {
		const auto& selectedView = _registry.view<Components::HighlightColor, Components::RenderColor, Components::IsSelected>();
		for (auto [entity, highlightColor, renderColor]: selectedView.each()) {
			renderColor.color = highlightColor.highlightColor;
		}
		const auto& defaultView = _registry.view<Components::HighlightColor, Components::RenderColor>(entt::exclude<Components::IsSelected>);
		for (auto [entity, highlightColor, renderColor]: defaultView.each()) {
			renderColor.color = highlightColor.defaultColor;
		}
	}
}