#pragma once

#include <clay.h>
#include <stdint.h>

typedef struct {
    Clay_Color bg_normal;
    Clay_Color bg_hover;
    Clay_Color bg_active;
    Clay_Color text_color;
    uint16_t border_radius;
    Clay_Padding padding;
    uint16_t font_size;
} ButtonStyle;

extern const ButtonStyle BUTTON_PRIMARY;
extern const ButtonStyle BUTTON_SECONDARY;
