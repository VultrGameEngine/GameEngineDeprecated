#pragma once
#include <ecs/system/system_provider.hpp>
#include <memory.h>
#include <ecs/world/world.hpp>
#include <GLFW/glfw3.h>
#include <engine.hpp>

namespace Vultr
{
class ControllerSystemProvider : public SystemProvider
{
  public:
    // Singleton pattern for all providers
    static std::shared_ptr<ControllerSystemProvider> Get()
    {
        return Engine::GetSystemProvider<ControllerSystemProvider>();
    }
    GLFWwindow *m_window;
    bool m_focused = false;

  protected:
    void OnDestroyEntity(Entity entity) override;
    void OnCreateEntity(Entity entity) override;
};
} // namespace Vultr
