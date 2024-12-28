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
#include "Components/Click.h"
#include "Components/Turn.h"
#include "Components/Presentation/NeedBounceAnimation.h"

namespace Sample::Systems::Utility {
	using namespace Components;
	using namespace Components::Presentation;

	EventCleanUpSystem::EventCleanUpSystem(entt::registry &registry) : _registry(registry) {}

	void EventCleanUpSystem::Update() {
		// TODO: code generation for event clean up
		CleanUp<ControlPress>();
		CleanUp<ControlDown>();
		CleanUp<MouseScroll>();
		CleanUp<MouseMove>();
		CleanUp<ActionStart>();
		CleanUp<ActionFinish>();
		CleanUp<WorldMovementIntent>();
		CleanUp<CameraMovementIntent>();
		CleanUp<CameraMovement>();
		CleanUp<Click>();
		CleanUp<Turn>();
		CleanUp<NeedBounceAnimation>();
	}
}