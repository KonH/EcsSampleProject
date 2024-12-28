#include "ButtonClickSystem.h"

#include "Components/BoxCollider.h"
#include "Components/Button.h"
#include "Components/Click.h"
#include "Components/ControlPress.h"
#include "Components/MousePosition.h"
#include "Components/ScreenPosition.h"
#include "Logging/Logger.h"
#include "Types/ControlType.h"
#include "Types/Vector2Int.h"

namespace Sample::Systems::UI {
	// TODO: click reaction
	// TODO: click sound

	using namespace Sample::Components;

	ButtonClickSystem::ButtonClickSystem(entt::registry& registry) : _registry(registry) {}

	void ButtonClickSystem::Update() {
		auto clickView = _registry.view<ControlPress>();
		auto buttonView = _registry.view<Button, ScreenPosition, BoxCollider>();
		const auto& mousePosition = _registry.ctx().get<MousePosition>().position;
		for (auto&& [clickEntity, controlPress]: clickView.each()) {
			if (controlPress.control != Types::ControlType::LeftMouseButton) {
				continue;
			}
			for (auto&& [entity, position, collider]: buttonView.each()) {
				if (mousePosition.x >= static_cast<float>(position.position.x) &&
					mousePosition.x <= static_cast<float>(position.position.x + collider.size.x) &&
					mousePosition.y >= static_cast<float>(position.position.y) &&
					mousePosition.y <= static_cast<float>(position.position.y + collider.size.y)) {
					Sample::Logging::Logger::LogInfo(
						"[ButtonClickSystem] Button clicked at position: {}x{}",
						mousePosition.x, mousePosition.y);
					_registry.emplace<Click>(entity);
				}
			}
		}
	}
}
