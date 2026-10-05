#pragma once

#include <clay.h>
#include <stdbool.h>

#include "ui/styles/button/button_style.h"

typedef void (*UiIconRenderer)(Clay_Color color);

bool ui_button(Clay_ElementId id, const char *label, const ButtonStyle *style);
bool ui_tab_button(Clay_ElementId id, const char *label, bool is_active, const ButtonStyle *style);
bool ui_tab_slot_button(Clay_ElementId id, const char *label, bool is_active,
                        UiIconRenderer render_icon, const ButtonStyle *style);
