#include "ui/views/content_view.h"

#include <clay.h>
#include <stdio.h>
#include <string.h>

#include "ui/styles/button/button_style.h"
#include "ui/widgets/button/button.h"

void content_view_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("ContentCard"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                   .padding = {24, 24, 24, 24},
                   .childGap = 16},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    char title_buf[64];
    snprintf(title_buf, sizeof(title_buf), "VIEW %d", state->active_tab + 1);
    Clay_String title_str = {
        .chars = title_buf, .length = (int32_t)strlen(title_buf), .isStaticallyAllocated = false};
    CLAY_TEXT(title_str, CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 22}));

    char desc_buf[128];
    snprintf(desc_buf, sizeof(desc_buf), "Active content area for button #%d.",
             state->active_tab + 1);
    Clay_String desc_str = {
        .chars = desc_buf, .length = (int32_t)strlen(desc_buf), .isStaticallyAllocated = false};
    CLAY_TEXT(desc_str, CLAY_TEXT_CONFIG({.textColor = {200, 200, 200, 255}, .fontSize = 16}));

    if (state->active_tab == 0) {
      char btn_text[64];
      if (state->click_count == 0) {
        snprintf(btn_text, sizeof(btn_text), "Action Button");
      } else {
        snprintf(btn_text, sizeof(btn_text), "Clicks: %d", state->click_count);
      }

      if (ui_button(CLAY_ID("ActionBtn"), btn_text, &button_monochrome)) {
        state->click_count++;
      }
    }
  }
}
