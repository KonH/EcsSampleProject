#include "EventCleanUpSystem.h"

#include "Components/ActionFinish.h"
#include "Components/ActionStart.h"
#include "Components/ControlPress.h"
#include "Components/WorldMovementIntent.h"

namespace Sample::Systems::Utility {
	EventCleanUpSystem::EventCleanUpSystem(entt::registry &registry) : _registry(registry) {}

	void EventCleanUpSystem::Update() {
		// TODO: code generation for event clean up
		CleanUp<Components::ControlPress>();
		CleanUp<Components::ActionStart>();
		CleanUp<Components::ActionFinish>();
		CleanUp<Components::WorldMovementIntent>();
	}
}