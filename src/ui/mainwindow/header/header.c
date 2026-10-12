#include "ui/mainwindow/header/header.h"

#include <clay.h>

HeaderActions header_render(const SvgIconCache *icons) {
  HeaderActions actions = {0};

  Clay_ElementId close_btn_id = CLAY_ID("WindowCloseBtn");
  Clay_ElementId min_btn_id = CLAY_ID("WindowMinBtn");
  Clay_ElementId settings_id = CLAY_ID("HeaderSettingsBtn");

  Clay_PointerData pointer = Clay_GetPointerState();

  bool close_hover = Clay_PointerOver(close_btn_id);
  bool min_hover = Clay_PointerOver(min_btn_id);
  bool settings_hover = Clay_PointerOver(settings_id);

  if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
    if (close_hover) {
      actions.close_clicked = true;
    }
    if (min_hover) {
      actions.minimize_clicked = true;
    }
    if (settings_hover) {
      actions.settings_clicked = true;
    }
  }

  // Top header bar container
  CLAY(CLAY_ID("HeaderBar"),
       {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(38)},
                   .padding = {14, 14, 0, 0},
                   .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 0, .right = 0, .top = 0, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // Left group: Logo + title
    CLAY(CLAY_ID("HeaderLeftGroup"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                     .childGap = 12,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
      if (icons && icons->logo) {
        CLAY_AUTO_ID(
            {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(22), .height = CLAY_SIZING_FIXED(22)}},
             .image = {.imageData = icons->logo}}) {
        }
      }

      CLAY_TEXT(CLAY_STRING("Welcome_to_VANE //"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 15}));
    }

    // Spacer
    CLAY(CLAY_ID("HeaderSpacer"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}}}) {
    }

    // Right group: SETTINGS button + window controls
    CLAY(CLAY_ID("HeaderRightGroup"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                     .childGap = 14,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
      // SETTINGS Button
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
        if (icons && icons->settings) {
          CLAY_AUTO_ID(
              {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(15),
                                     .height = CLAY_SIZING_FIXED(15)}},
               .image = {.imageData = icons->settings}}) {
          }
        }
        CLAY_TEXT(CLAY_STRING("SETTINGS"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 13}));
      }

      // Window Control Buttons (Minimize, Close)
      CLAY(CLAY_ID("HeaderWindowControls"),
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIXED(28)},
                       .childGap = 6,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
        // Minimize Button
        CLAY(min_btn_id,
             {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(28), .height = CLAY_SIZING_FIXED(28)},
                         .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
              .backgroundColor =
                  min_hover ? (Clay_Color){40, 40, 40, 255} : (Clay_Color){0, 0, 0, 255}}) {
          CLAY_TEXT(CLAY_STRING("-"),
                    CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 16}));
        }

        // Close Button
        CLAY(close_btn_id,
             {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(28), .height = CLAY_SIZING_FIXED(28)},
                         .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
              .backgroundColor =
                  close_hover ? (Clay_Color){180, 40, 40, 255} : (Clay_Color){0, 0, 0, 255}}) {
          CLAY_TEXT(CLAY_STRING("X"),
                    CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 14}));
        }
      }
    }
  }

  return actions;
}
