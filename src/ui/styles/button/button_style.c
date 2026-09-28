#include "ui/styles/button/button_style.h"

// Strict rectangular monochrome style:
// Default: black background, 1px white border, white text
// Active: white background, 1px black border, black text (inverted)
const ButtonStyle button_monochrome = {
    .bg_normal = (Clay_Color){0, 0, 0, 255},
    .text_normal = (Clay_Color){255, 255, 255, 255},
    .border_normal = (Clay_Color){255, 255, 255, 255},

    .bg_hover = (Clay_Color){35, 35, 35, 255},
    .text_hover = (Clay_Color){255, 255, 255, 255},
    .border_hover = (Clay_Color){255, 255, 255, 255},

    .bg_active = (Clay_Color){255, 255, 255, 255},
    .text_active = (Clay_Color){0, 0, 0, 255},
    .border_active = (Clay_Color){0, 0, 0, 255},

    .bg_active_hover = (Clay_Color){230, 230, 230, 255},
    .text_active_hover = (Clay_Color){0, 0, 0, 255},
    .border_active_hover = (Clay_Color){0, 0, 0, 255},

    .border_width = 1,
    .border_radius = 0,
    .padding = {.left = 16, .right = 16, .top = 10, .bottom = 10},
    .font_size = 16,
};

const ButtonStyle button_primary = {
    .bg_normal = (Clay_Color){0, 0, 0, 255},
    .text_normal = (Clay_Color){255, 255, 255, 255},
    .border_normal = (Clay_Color){255, 255, 255, 255},

    .bg_hover = (Clay_Color){35, 35, 35, 255},
    .text_hover = (Clay_Color){255, 255, 255, 255},
    .border_hover = (Clay_Color){255, 255, 255, 255},

    .bg_active = (Clay_Color){255, 255, 255, 255},
    .text_active = (Clay_Color){0, 0, 0, 255},
    .border_active = (Clay_Color){0, 0, 0, 255},

    .bg_active_hover = (Clay_Color){230, 230, 230, 255},
    .text_active_hover = (Clay_Color){0, 0, 0, 255},
    .border_active_hover = (Clay_Color){0, 0, 0, 255},

    .border_width = 1,
    .border_radius = 0,
    .padding = {.left = 16, .right = 16, .top = 10, .bottom = 10},
    .font_size = 16,
};

const ButtonStyle button_secondary = {
    .bg_normal = (Clay_Color){20, 20, 20, 255},
    .text_normal = (Clay_Color){200, 200, 200, 255},
    .border_normal = (Clay_Color){100, 100, 100, 255},

    .bg_hover = (Clay_Color){45, 45, 45, 255},
    .text_hover = (Clay_Color){255, 255, 255, 255},
    .border_hover = (Clay_Color){160, 160, 160, 255},

    .bg_active = (Clay_Color){255, 255, 255, 255},
    .text_active = (Clay_Color){0, 0, 0, 255},
    .border_active = (Clay_Color){0, 0, 0, 255},

    .bg_active_hover = (Clay_Color){230, 230, 230, 255},
    .text_active_hover = (Clay_Color){0, 0, 0, 255},
    .border_active_hover = (Clay_Color){0, 0, 0, 255},

    .border_width = 1,
    .border_radius = 0,
    .padding = {.left = 16, .right = 16, .top = 10, .bottom = 10},
    .font_size = 16,
};
