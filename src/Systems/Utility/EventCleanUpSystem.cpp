#include "EventCleanUpSystem.h"

#include "Events/ControlPress.h"
#include "Events/WorldMovement.h"

namespace Sample::Systems::Utility {
	EventCleanUpSystem::EventCleanUpSystem(entt::registry &registry) : _registry(registry) {}

	void EventCleanUpSystem::Update() {
		CleanUp<Events::ControlPress>();
		CleanUp<Events::WorldMovement>();
	}
}