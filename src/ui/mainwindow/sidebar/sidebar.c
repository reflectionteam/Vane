#include "ui/mainwindow/sidebar/sidebar.h"

#include <SDL3/SDL.h>
#include <clay.h>

#include "ui/styles/button/button_style.h"
#include "ui/widgets/button/button.h"
#include "ui/widgets/icon/icons.h"

void sidebar_render(AppState *state) {
  if (!state) {
    return;
  }

  CLAY(CLAY_ID("LeftSidebar"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(210), .height = CLAY_SIZING_GROW(0)},
                   .padding = {14, 14, 16, 16},
                   .childGap = 10},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 0, .right = 1, .top = 0, .bottom = 0, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    static const char *button_labels[TAB_COUNT] = {"OVERVIEW", "MODS", "SERVERS", "SCREENSHOTS",
                                                   "LOGS"};

    static UiIconRenderer icon_renderers[TAB_COUNT] = {
        ui_icon_overview, ui_icon_mods, ui_icon_servers, ui_icon_screenshots, ui_icon_logs};

    // 1. Navigation buttons with dual-slot (icon + label)
    for (int i = 0; i < TAB_COUNT; i++) {
      if (ui_tab_slot_button(CLAY_IDI("SidebarTab", i), button_labels[i],
                             state->active_tab == (AppTab)i, icon_renderers[i],
                             &button_monochrome)) {
        state->active_tab = (AppTab)i;
        SDL_Log("Selected: %s", button_labels[i]);
      }
    }

    // 2. Spacer to push account card to bottom
    CLAY(CLAY_ID("SidebarSpacer"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}}}) {
    }

    // 3. Account card template (avatar slot + NICKNAME // + ACCOUNT_TYPE + chevron)
    CLAY(CLAY_ID("AccountCard"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(48)},
                     .padding = {8, 8, 6, 6},
                     .childGap = 10,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
          .border = {.color = (Clay_Color){255, 255, 255, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      // Avatar placeholder box (empty bordered square)
      CLAY(CLAY_ID("AvatarSlot"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(32), .height = CLAY_SIZING_FIXED(32)},
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
            .border =
                {.color = (Clay_Color){255, 255, 255, 255},
                 .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor = (Clay_Color){20, 20, 20, 255}}) {
      }

      // Account name and type placeholders
      CLAY(CLAY_ID("AccountTextCol"),
           {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                       .childGap = 2,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
        CLAY_TEXT(CLAY_STRING("NICKNAME //"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 13}));
        CLAY_TEXT(CLAY_STRING("ACCOUNT_TYPE"),
                  CLAY_TEXT_CONFIG({.textColor = {150, 150, 150, 255}, .fontSize = 11}));
      }

      // Expand chevron
      CLAY(CLAY_ID("AccountChevron"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                       .childAlignment = {.x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_CENTER}}}) {
        CLAY_TEXT(CLAY_STRING("^"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 14}));
      }
    }
  }
}
