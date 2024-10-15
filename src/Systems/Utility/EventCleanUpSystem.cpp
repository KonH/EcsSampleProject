#include "EventCleanUpSystem.h"

#include "Components/ActionFinish.h"
#include "Components/ActionStart.h"
#include "Components/ControlPress.h"
#include "Components/ControlDown.h"
#include "Components/MouseScroll.h"
#include "Components/MouseMove.h"
#include "Components/WorldMovementIntent.h"
#include "Components/CameraMovementIntent.h"
#include "Components/CameraMovement.h"

namespace Sample::Systems::Utility {
	EventCleanUpSystem::EventCleanUpSystem(entt::registry &registry) : _registry(registry) {}

	void EventCleanUpSystem::Update() {
		// TODO: code generation for event clean up
		CleanUp<Components::ControlPress>();
		CleanUp<Components::ControlDown>();
		CleanUp<Components::MouseScroll>();
		CleanUp<Components::MouseMove>();
		CleanUp<Components::ActionStart>();
		CleanUp<Components::ActionFinish>();
		CleanUp<Components::WorldMovementIntent>();
		CleanUp<Components::CameraMovementIntent>();
		CleanUp<Components::CameraMovement>();
	}
}