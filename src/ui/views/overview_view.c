#include "ui/views/overview_view.h"

#include <clay.h>
#include <stdio.h>

#include "ui/styles/button/button_style.h"
#include "ui/widgets/button/button.h"

void overview_view_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("OverviewCard"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                   .padding = {24, 24, 24, 24},
                   .childGap = 16},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    CLAY_TEXT(CLAY_STRING("TAB: OVERVIEW"),
              CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 22}));
    CLAY_TEXT(CLAY_STRING("Monolithic UI: 0px corner radius, strict B&W style."),
              CLAY_TEXT_CONFIG({.textColor = {200, 200, 200, 255}, .fontSize = 16}));

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
