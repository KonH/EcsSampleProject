#include "SystemsBuilder.h"

#include "Frontend/FrontendSystems.h"

#include "Animation/MovementAnimationSystem.h"

#include "Movement/WorldMovementSystem.h"

#include "Presentation/HighlightCellByMousePositionSystem.h"
#include "Presentation/WorldToScreenPositionSystem.h"
#include "Presentation/WorldToScreenPositionSetSystem.h"
#include "Presentation/ScreenToRenderPositionSystem.h"
#include "Presentation/ScreenToRenderPositionSetSystem.h"
#include "Presentation/HighlightSelectedSystem.h"
#include "Presentation/ResourceCounterUpdateSystem.h"

#include "Utility/ActionProgressCleanUpSystem.h"
#include "Utility/ActionProgressUpdateSystem.h"
#include "Utility/DeltaTimeUpdateSystem.h"
#include "Utility/EventCleanUpSystem.h"

#include "Camera/CameraZoomSystem.h"
#include "Camera/CameraMovementIntentSystem.h"
#include "Camera/CameraMovementSystem.h"

#include "Selection/MouseArmySelectionSystem.h"

namespace Sample::Systems {
	void SystemsBuilder::PreMainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		Add<Utility::DeltaTimeUpdateSystem>(registry, systems);
	}

	void SystemsBuilder::MainInitialize(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		Add<Utility::ActionProgressUpdateSystem>(registry, systems);
		Add<Selection::MouseArmySelectionSystem>(registry, systems);
		Add<Presentation::HighlightSelectedSystem>(registry, systems);
		Add<Movement::WorldMovementSystem>(registry, systems);
		Add<Presentation::ResourceCounterUpdateSystem>(registry, systems);
		Add<Presentation::HighlightCellByMousePositionSystem>(registry, systems);
		Add<Presentation::WorldToScreenPositionSystem>(registry, systems);
		Add<Presentation::WorldToScreenPositionSetSystem>(registry, systems);
		Add<Animation::MovementAnimationSystem>(registry, systems);
		Add<Presentation::ScreenToRenderPositionSystem>(registry, systems);
		Add<Presentation::ScreenToRenderPositionSetSystem>(registry, systems);
		Add<Camera::CameraZoomSystem>(registry, systems);
		Add<Camera::CameraMovementIntentSystem>(registry, systems);
		Add<Camera::CameraMovementSystem>(registry, systems);
	}

	void SystemsBuilder::PostMainInitialize(entt::registry &registry, std::vector<std::unique_ptr<Systems::System>> &systems) {
		Add<Utility::ActionProgressCleanUpSystem>(registry, systems);
		Add<Utility::EventCleanUpSystem>(registry, systems);
	}


}