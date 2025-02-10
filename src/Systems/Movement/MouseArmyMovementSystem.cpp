#include "MouseArmyMovementSystem.h"

#include "Components/ActionProgress.h"
#include "Components/ControlDown.h"
#include "Components/IsPlayer.h"
#include "Components/WorldMovementIntent.h"
#include "Components/WorldPosition.h"
#include "Components/MousePosition.h"
#include "Components/IsSelected.h"
#include "Components/Province.h"
#include "Components/HasOwner.h"
#include "Components/RenderSettings.h"
#include "Components/ControlPress.h"
#include "Utils/VectorUtils.h"
#include "Logging/Logger.h"

namespace Sample::Systems::Movement {
	MouseArmyMovementSystem::MouseArmyMovementSystem(entt::registry& registry) : _registry(registry) {}

	void MouseArmyMovementSystem::Update() {
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();
		const auto& center = VectorUtils::GetScreenCenter(renderSettings);
		const auto& mousePosition = _registry.ctx().get<Components::MousePosition>();
		const auto& worldPosition = VectorUtils::ToWorldPosition(renderSettings, center, mousePosition.position);
		const auto& worldPositionFloor = Types::Vector2Float { std::floor(worldPosition.x), std::floor(worldPosition.y) };

		for (auto&& [_, controlPress] : _registry.view<Components::ControlPress>().each()) {
			if (controlPress.control == Types::ControlType::LeftMouseButton) {
				auto armyView = _registry.view<Components::IsPlayer, Components::IsSelected, Components::WorldPosition, Components::HasOwner>();
				for (auto&& [armyEntity, armyWorldPosition, armyOwner]: armyView.each()) {
					auto provinceView = _registry.view<Components::Province, Components::WorldPosition>();
					for (auto&& [provinceEntity, provinceWorldPosition]: provinceView.each()) {
						// TODO: simplify click on entity logic (helper component + system)
						if (worldPositionFloor != provinceWorldPosition.position) {
							continue;
						}
						if (const auto& provinceOwner = _registry.try_get<Components::HasOwner>(provinceEntity)) {
							if (provinceOwner->owner != armyOwner.owner) {
								Logging::Logger::LogInfo("[MouseArmyMovementSystem] Target province have other owner");
								continue;
							}
						}
						const auto& provincePosition = provinceWorldPosition.position;
						const auto& armyPosition = armyWorldPosition.position;
						const auto xDiff = provincePosition.x - armyPosition.x;
						const auto yDiff = provincePosition.y - armyPosition.y;
						const auto xDiffAbs = std::abs(xDiff);
						const auto yDiffAbs = std::abs(yDiff);
						if (xDiffAbs > 1 || yDiffAbs > 1) {
							Logging::Logger::LogInfo("[MouseArmyMovementSystem] Target province is too far");
							continue;
						}
						Logging::Logger::LogInfo("[MouseArmyMovementSystem] Move army");
						_registry.emplace<Components::WorldMovementIntent>(
							armyEntity, Components::WorldMovementIntent { Types::Vector2Float { xDiff, yDiff } });
					}
				}
			}
		}
	}
}