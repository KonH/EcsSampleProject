#pragma once
#ifdef USE_RENDER_RAYLIB
#include <entt/entity/registry.hpp>

#include "Systems/System.h"

namespace Sample::Systems::Raylib {
  class AppWindowInitSystem final : public System {
  public:
    explicit AppWindowInitSystem(entt::registry& registry);

    void Init() override;

  private:
    entt::registry& _registry;
  };
}
#endif