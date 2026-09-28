#include "ui/views/sidebar.h"

#include <SDL3/SDL.h>
#include <clay.h>

#include "ui/styles/button/button_style.h"
#include "ui/widgets/button/button.h"

void sidebar_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("RightSidebar"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(220), .height = CLAY_SIZING_GROW(0)},
                   .padding = {16, 16, 24, 24},
                   .childGap = 12},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 0, .top = 0, .bottom = 0, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    CLAY_TEXT(CLAY_STRING("MENU"),
              CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 16}));

    if (ui_tab_button(CLAY_ID("TabBtnOverview"), "Overview", state->active_tab == TAB_OVERVIEW,
                      &button_monochrome)) {
      state->active_tab = TAB_OVERVIEW;
      SDL_Log("Selected tab: Overview");
    }
    if (ui_tab_button(CLAY_ID("TabBtnProjects"), "Projects", state->active_tab == TAB_PROJECTS,
                      &button_monochrome)) {
      state->active_tab = TAB_PROJECTS;
      SDL_Log("Selected tab: Projects");
    }
    if (ui_tab_button(CLAY_ID("TabBtnSettings"), "Settings", state->active_tab == TAB_SETTINGS,
                      &button_monochrome)) {
      state->active_tab = TAB_SETTINGS;
      SDL_Log("Selected tab: Settings");
    }
  }
}
