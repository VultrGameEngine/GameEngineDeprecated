#pragma once
#include "gui_vertex.h"
#include <array>
#include "../framework/size.h"

namespace Vultr
{
namespace GUI
{

using QuadID = int;
using VertexID = int;
using IndexID = int;
using Zindex = int;
using RenderGroupID = unsigned int;

struct QuadProperties
{
    QuadProperties() = default;

    Vec4 color = Vec4(1);
    Size size = Size(0, 0);
    double rotation = 0;
    Vec2 uv = Vec2(0, 0);
    Vec2 uv_dimensions = Vec2(0, 0);
    Vec2 texture_dimensions = Vec2(0, 0);
    Vec4 border_widths = Vec4(0);
    Vec4 border_color = Vec4(0);
};

class BuildContext;

class Quad
{
  public:
    Quad(bool p_has_texture = false) : has_texture(p_has_texture)
    {
    }

    void Commit(QuadID id, const QuadProperties &properties, BuildContext *context);

  private:
    GUIVertex vertices[4];
    bool has_texture = false;
};
} // namespace GUI
} // namespace Vultr
