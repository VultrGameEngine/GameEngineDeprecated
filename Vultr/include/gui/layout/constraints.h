#pragma once
#include <types/types.hpp>

namespace Vultr
{
    namespace IMGUI
    {
        struct Constraints
        {
            f32 min_width = 0;
            f32 min_height = 0;
            f32 max_width = 0;
            f32 max_height = 0;
            Constraints() = default;
            Constraints(Vec2 min, Vec2 max) : min_width(min.x), min_height(min.y), max_width(max.x), max_height(max.y){};
            Constraints(f32 p_min_width, f32 p_max_width, f32 p_min_height, f32 p_max_height) : min_width(p_min_width), min_height(p_min_height), max_width(p_max_width), max_height(p_max_height){};
        };

        Constraints loose_constraints(Vec2 size);
        Constraints tight(Vec2 size);
        Constraints generate_loose(const Constraints &c);
        void generate_constraints(const Constraints &c, Constraints &other);

        Vec2 constraints_max(const Constraints &c);
        Vec2 constraints_min(const Constraints &c);

        Vec2 get_size_from_constraints(const Constraints &c, Vec2 size);

    } // namespace IMGUI
} // namespace Vultr