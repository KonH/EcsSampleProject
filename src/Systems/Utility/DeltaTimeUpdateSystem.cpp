#include "DeltaTimeUpdateSystem.h"

#include <chrono>

#include "Components/Runtime.h"

namespace Sample::Systems::Utility {
	DeltaTimeUpdateSystem::DeltaTimeUpdateSystem(entt::registry &registry) : _registry(registry), _lastUpdateTime(0.0f) {}

	void DeltaTimeUpdateSystem::Update() {
		auto& runtime = _registry.ctx().get<Components::Runtime>();
		const auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
		const auto timeSinceEpochMs = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();
		const auto deltaTime = static_cast<float>(timeSinceEpochMs - _lastUpdateTime) / 1000.0f;
		runtime.deltaTime = (_lastUpdateTime > 0) ? deltaTime : 0.0f;
		_lastUpdateTime = timeSinceEpochMs;
	}
}