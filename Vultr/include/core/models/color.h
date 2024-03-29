#pragma once
#include <fundamental/types.h>

namespace Vultr
{
    struct Color
    {
        Color() : value(Vec4(0, 0, 0, 1))
        {
        }
        Color(Vec4 p_value) : value(p_value)
        {
        }
        Vec4 value;
    };
} // namespace Vultr
