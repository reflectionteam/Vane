#pragma once

#include <stdbool.h>
#include <clay.h>
#include "ui/styles/button_style.h"

// Renders a styled button widget.
// Returns true on the frame the button is clicked.
bool UI_Button(Clay_ElementId id, const char *label, const ButtonStyle *style);
