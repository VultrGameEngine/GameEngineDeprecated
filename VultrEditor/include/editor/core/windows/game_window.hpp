#pragma once
#include <editor/imgui/window.hpp>

namespace Vultr::Editor
{
class GameWindow : public Window
{
  public:
    void Render() override;
};
}; // namespace Vultr::Editor