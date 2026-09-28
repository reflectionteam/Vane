#pragma once

#include <clay.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  // Inactive / Normal state
  Clay_Color bg_normal;
  Clay_Color text_normal;
  Clay_Color border_normal;

  // Inactive Hover state
  Clay_Color bg_hover;
  Clay_Color text_hover;
  Clay_Color border_hover;

  // Active (selected / pressed) state - inverted colors
  Clay_Color bg_active;
  Clay_Color text_active;
  Clay_Color border_active;

  // Active Hover state
  Clay_Color bg_active_hover;
  Clay_Color text_active_hover;
  Clay_Color border_active_hover;

  uint16_t border_width;
  uint16_t border_radius; // 0 for strict rectangular design
  Clay_Padding padding;
  uint16_t font_size;
} ButtonStyle;

// Strict rectangular monochrome style:
// Default: black background, 1px white border, white text
// Active: white background, 1px black border, black text (inverted)
extern const ButtonStyle button_monochrome;
extern const ButtonStyle button_primary;
extern const ButtonStyle button_secondary;

#define BUTTON_MONOCHROME button_monochrome
#define BUTTON_PRIMARY button_primary
#define BUTTON_SECONDARY button_secondary
