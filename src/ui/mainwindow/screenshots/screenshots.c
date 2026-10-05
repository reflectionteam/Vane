#include "ui/mainwindow/screenshots/screenshots.h"

#include <clay.h>

void screenshots_init(ScreenshotsState *state) {
  if (!state) {
    return;
  }
  state->dummy = 0;
}

void screenshots_render(ScreenshotsState *state) {
  (void)state;

  CLAY(CLAY_ID("ScreenshotsContent"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                   .padding = {20, 20, 20, 20},
                   .childGap = 16},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    CLAY(CLAY_ID("ScreenshotsHeaderBox"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                     .padding = {10, 12, 4, 4}},
          .border = {.color = (Clay_Color){255, 255, 255, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      CLAY_TEXT(CLAY_STRING("SCREENSHOTS //"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 20}));
    }

    CLAY(CLAY_ID("ScreenshotsPlaceholderCard"),
         {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                     .padding = {16, 16, 16, 16},
                     .childGap = 8},
          .border = {
              .color = (Clay_Color){100, 100, 100, 255},
              .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
      CLAY_TEXT(CLAY_STRING("NO_SCREENSHOTS_FOUND"),
                CLAY_TEXT_CONFIG({.textColor = {180, 180, 180, 255}, .fontSize = 13}));
    }
  }
}
