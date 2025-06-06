#pragma once

namespace Aethereal::Enum::Unicode
{
    enum class BoxLight
    {
        HORIZONTAL = 0x2500,
        VERTICAL = 0x2502,
        TOP_LEFT = 0x250C,
        TOP_RIGHT = 0x2510,
        BOTTOM_LEFT = 0x2514,
        BOTTOM_RIGHT = 0x2518,
        VERTICAL_AND_RIGHT = 0x251C,
        VERTICAL_AND_LEFT = 0x2524,
        TOP_T_INTERSECTION = 0x252C,
        BOTTOM_T_INTERSECTION = 0x2534,
        CROSS = 0x253C
    };

    enum class BoxHeavy
    {
        HORIZONTAL = 0x2501,
        VERTICAL = 0x2503,
        TOP_LEFT = 0x250F,
        TOP_RIGHT = 0x2513,
        BOTTOM_LEFT = 0x2517,
        BOTTOM_RIGHT = 0x251B,
        VERTICAL_AND_RIGHT = 0x2523,
        VERTICAL_AND_LEFT = 0x252B,
        TOP_T_INTERSECTION = 0x252F,
        BOTTOM_T_INTERSECTION = 0x2533,
        CROSS = 0x254B
    };

    enum class Arrow
    {
        UP = 0x2191,
        DOWN = 0x2193,
        LEFT = 0x2190,
        RIGHT = 0x2192,
    };

    enum class Misc
    {
        STAR = 0x2605,
        CENTER_DOT = 0x2219,
    };
}
