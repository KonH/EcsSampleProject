#include "MainLoopRunner.h"

#include "Components/Runtime.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Sample::Execution {
	void MainLoop([[maybe_unused]] entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems) {
		for (const auto& system : systems) {
			system->Update();
		}

#ifdef __EMSCRIPTEN__
		if (!registry.ctx().get<Components::Runtime>().isRunning) {
			emscripten_cancel_main_loop();
		}
#endif
	}

	MainLoopRunner::MainLoopRunner(entt::registry& registry, std::vector<std::unique_ptr<Systems::System>>& systems)
		: _registry(registry), _systems(systems) {}

	void MainLoopRunner::Run() {
#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg([](void* arg) {
			auto& runner = *static_cast<MainLoopRunner*>(arg);
			MainLoop(runner._registry, runner._systems);
		}, this, 0, 1);
#else
		while (_registry.ctx().get<Components::Runtime>().isRunning) {
			MainLoop(_registry, _systems);
		}
#endif
	}
}