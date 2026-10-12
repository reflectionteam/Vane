#pragma once

#include <clay.h>
#include <stdbool.h>

#include "ui/styles/button/button_style.h"

#include <SDL3/SDL.h>

typedef void (*UiIconRenderer)(Clay_Color color);

bool ui_button(Clay_ElementId id, const char *label, const ButtonStyle *style);
bool ui_tab_button(Clay_ElementId id, const char *label, bool is_active, const ButtonStyle *style);
bool ui_tab_slot_button(Clay_ElementId id, const char *label, bool is_active,
                        UiIconRenderer render_icon, const ButtonStyle *style);
bool ui_tab_texture_button(Clay_ElementId id, const char *label, bool is_active,
                           SDL_Texture *icon_texture, float icon_w, float icon_h,
                           const ButtonStyle *style);
