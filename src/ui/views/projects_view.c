#include "ui/views/projects_view.h"

#include <clay.h>

void projects_view_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("ProjectsCard"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                   .padding = {24, 24, 24, 24},
                   .childGap = 16},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    CLAY_TEXT(CLAY_STRING("TAB: PROJECTS"),
              CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 22}));
    CLAY_TEXT(CLAY_STRING("Your active projects and workspaces will appear here."),
              CLAY_TEXT_CONFIG({.textColor = {200, 200, 200, 255}, .fontSize = 16}));
  }
}
