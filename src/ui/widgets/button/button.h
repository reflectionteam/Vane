#pragma once

#include <clay.h>
#include <stdbool.h>
#include "ui/styles/button/button_style.h"

// Renders a simple push button.
// Returns true on the frame the button is clicked.
bool ui_button(Clay_ElementId id, const char *label, const ButtonStyle *style);

// Renders a tab / selectable button with an active (selected) state.
// When is_active is true, colors are inverted.
// Stretches to fill container width if placed in a flex layout.
// Returns true on the frame the button is clicked.
bool ui_tab_button(Clay_ElementId id, const char *label, bool is_active, const ButtonStyle *style);

#define UI_Button ui_button
#define UI_TabButton ui_tab_button
