#ifdef USE_RENDER_RAYLIB
#include "AppWindowInitSystem.h"

#include <raylib.h>

#include "Components/Raylib/AppWindow.h"
#include "Components/RenderSettings.h"

namespace Sample::Systems::Raylib {
	AppWindowInitSystem::AppWindowInitSystem(entt::registry &registry) : _registry(registry) {}

	void AppWindowInitSystem::Init() {
		const auto& renderSettings = _registry.ctx().get<Components::RenderSettings>();

		InitWindow(renderSettings.screenWidth, renderSettings.screenHeight, renderSettings.windowTitle.c_str());
		SetTargetFPS(60);

		auto& appWindow = _registry.ctx().emplace<Components::Raylib::AppWindow>();
		appWindow.window = GetWindowHandle();
	}
}
#endif