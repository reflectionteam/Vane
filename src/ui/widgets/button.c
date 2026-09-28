#include "ui/widgets/button.h"
#include <string.h>

bool UI_Button(Clay_ElementId id, const char *label, const ButtonStyle *style) {
    if (!style) {
        style = &BUTTON_PRIMARY;
    }

    Clay_PointerData pointer = Clay_GetPointerState();
    bool hovered = Clay_PointerOver(id);
    bool pressed = hovered && (pointer.state == CLAY_POINTER_DATA_PRESSED || pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME);
    bool clicked = hovered && (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME);

    Clay_Color bg = style->bg_normal;
    if (pressed) {
        bg = style->bg_active;
    } else if (hovered) {
        bg = style->bg_hover;
    }

    Clay_String text_str = (Clay_String){
        .chars = label ? label : "",
        .length = (int32_t)(label ? strlen(label) : 0),
        .isStaticallyAllocated = false,
    };

    CLAY(id, {
        .layout = {
            .padding = style->padding,
            .childAlignment = {
                .x = CLAY_ALIGN_X_CENTER,
                .y = CLAY_ALIGN_Y_CENTER
            }
        },
        .cornerRadius = CLAY_CORNER_RADIUS(style->border_radius),
        .backgroundColor = bg
    }) {
        CLAY_TEXT(text_str, CLAY_TEXT_CONFIG({
            .textColor = style->text_color,
            .fontSize = style->font_size
        }));
    }

    return clicked;
}
