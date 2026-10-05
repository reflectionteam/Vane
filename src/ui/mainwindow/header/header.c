#include "ui/mainwindow/header/header.h"

#include <clay.h>

#include "ui/widgets/icon/icons.h"

HeaderActions header_render(void) {
  HeaderActions actions = {0};

  Clay_PointerData pointer = Clay_GetPointerState();

  // Settings button state
  Clay_ElementId settings_id = CLAY_ID("HeaderSettingsBtn");
  bool settings_hover = Clay_PointerOver(settings_id);
  if (settings_hover && (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)) {
    actions.settings_clicked = true;
  }

  // Minimize button state
  Clay_ElementId min_id = CLAY_ID("HeaderMinBtn");
  bool min_hover = Clay_PointerOver(min_id);
  if (min_hover && (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)) {
    actions.minimize_clicked = true;
  }

  // Close button state
  Clay_ElementId close_id = CLAY_ID("HeaderCloseBtn");
  bool close_hover = Clay_PointerOver(close_id);
  if (close_hover && (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)) {
    actions.close_clicked = true;
  }

  CLAY(CLAY_ID("HeaderBar"),
       {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(44)},
                   .padding = {16, 16, 8, 8},
                   .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 0, .right = 0, .top = 0, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // Left group: Logo slot + title
    CLAY(CLAY_ID("HeaderLeftGroup"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                     .childGap = 12,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
      ui_icon_logo_slot((Clay_Color){255, 255, 255, 255});

      CLAY_TEXT(CLAY_STRING("WELCOME_TO_VANE //"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 15}));
    }

    // Spacer
    CLAY(CLAY_ID("HeaderSpacer"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}}}) {
    }

    // Right group: SETTINGS + Minimize + Close
    CLAY(CLAY_ID("HeaderRightGroup"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                     .childGap = 14,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
      // SETTINGS button
      CLAY(settings_id,
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIXED(28)},
                       .padding = {10, 10, 4, 4},
                       .childGap = 8,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
            .border =
                {.color = (Clay_Color){255, 255, 255, 255},
                 .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor =
                settings_hover ? (Clay_Color){40, 40, 40, 255} : (Clay_Color){0, 0, 0, 255}}) {
        ui_icon_settings((Clay_Color){255, 255, 255, 255});
        CLAY_TEXT(CLAY_STRING("SETTINGS"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 13}));
      }

      // Minimize button
      CLAY(min_id,
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(28), .height = CLAY_SIZING_FIXED(28)},
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
            .backgroundColor =
                min_hover ? (Clay_Color){40, 40, 40, 255} : (Clay_Color){0, 0, 0, 255}}) {
        CLAY_TEXT(CLAY_STRING("-"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 18}));
      }

      // Close button
      CLAY(close_id,
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(28), .height = CLAY_SIZING_FIXED(28)},
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
            .backgroundColor =
                close_hover ? (Clay_Color){80, 0, 0, 255} : (Clay_Color){0, 0, 0, 255}}) {
        CLAY_TEXT(CLAY_STRING("X"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 15}));
      }
    }
  }

  return actions;
}
