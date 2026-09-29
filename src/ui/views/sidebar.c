#include "ui/views/sidebar.h"

#include <SDL3/SDL.h>
#include <clay.h>

#include "ui/styles/button/button_style.h"
#include "ui/widgets/button/button.h"

void sidebar_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("LeftSidebar"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(220), .height = CLAY_SIZING_GROW(0)},
                   .padding = {16, 16, 24, 24},
                   .childGap = 12},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 0, .right = 1, .top = 0, .bottom = 0, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    static const char *button_labels[5] = {"Button 1", "Button 2", "Button 3", "Button 4",
                                           "Button 5"};

    for (int i = 0; i < 5; i++) {
      if (ui_tab_button(CLAY_IDI("SidebarBtn", i), button_labels[i], state->active_tab == i,
                        &button_monochrome)) {
        state->active_tab = i;
        SDL_Log("Selected: %s", button_labels[i]);
      }
    }
  }
}
