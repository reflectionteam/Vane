#include "ui/styles/button_style.h"

const ButtonStyle BUTTON_PRIMARY = {
    .bg_normal = (Clay_Color){59, 130, 246, 255},
    .bg_hover = (Clay_Color){37, 99, 235, 255},
    .bg_active = (Clay_Color){29, 78, 216, 255},
    .text_color = (Clay_Color){255, 255, 255, 255},
    .border_radius = 8,
    .padding = { .left = 20, .right = 20, .top = 10, .bottom = 10 },
    .font_size = 18,
};

const ButtonStyle BUTTON_SECONDARY = {
    .bg_normal = (Clay_Color){55, 65, 81, 255},
    .bg_hover = (Clay_Color){75, 85, 99, 255},
    .bg_active = (Clay_Color){31, 41, 55, 255},
    .text_color = (Clay_Color){243, 244, 246, 255},
    .border_radius = 8,
    .padding = { .left = 20, .right = 20, .top = 10, .bottom = 10 },
    .font_size = 18,
};
