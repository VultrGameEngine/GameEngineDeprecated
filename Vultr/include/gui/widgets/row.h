#pragma once
#include <gui/core/context.h>
#include <gui/layout/alignment.h>
#include <gui/layout/flex_size.h>
#include <gui/layout/direction.h>

namespace Vultr
{
    namespace IMGUI
    {
        struct RowStyle
        {
            MainAxisAlignment main_axis_alignment = MainAxisAlignment::START;
            MainAxisSize main_axis_size = MainAxisSize::MAX;
            CrossAxisAlignment cross_axis_alignment = CrossAxisAlignment::CENTER;
            HorizontalDirection horizontal_direction = HorizontalDirection::LEFT_TO_RIGHT;
            VerticalDirection vertical_direction = VerticalDirection::DOWN;
        };

        struct RowState
        {
            RowStyle style = {};

            // The number of possible elements that could fill widget_order
            size_t widget_order_size = 0;

            // Array of widgets which are in order of appearance
            UI_ID *widget_order = nullptr;

            // Stores the current index that we are rendering for
            u32 index = 0;

            // Values to keep track of. NOTE: total_width becomes irrelevant once flex_mode becomes true
            f32 total_width = 0;
            f32 max_height = 0;

            // The available space that this row can fit into. This is used for flex factors
            f32 available_width = UNBOUNDED;

            // Used to verify that the flex total is indeed correct compared to the flex factors.
            f32 flex_accumulator = 0;
        };

        void begin_row(Context *c, UI_ID id, RowStyle style = {});

        // All elements in a row must be wrapped with a begin and end row element
        void begin_row_element(Context *c, s32 index = -1, f32 flex_factor = -1);
        void end_row_element(Context *c);

        void end_row(Context *c);
    } // namespace IMGUI
} // namespace Vultr
