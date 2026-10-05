#include "ui/mainwindow/overview/overview.h"

#include <clay.h>
#include <string.h>

#include "ui/widgets/icon/icons.h"

void overview_init(OverviewState *state) {
  if (!state) {
    return;
  }
  state->dummy = 0;
}

static void render_instance_card(Clay_ElementId id, const char *name, const char *version) {
  Clay_PointerData pointer = Clay_GetPointerState();
  bool hovered = Clay_PointerOver(id);

  Clay_Color border_color =
      hovered ? (Clay_Color){255, 255, 255, 255} : (Clay_Color){200, 200, 200, 255};

  CLAY(id,
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(116), .height = CLAY_SIZING_FIT(0)},
                   .padding = {6, 6, 6, 6},
                   .childGap = 6},
        .border = {.color = border_color,
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // 1. Thumbnail placeholder box (no real images, clean geometric placeholder)
    CLAY_AUTO_ID(
        {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(104)},
                    .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
         .border = {.color = (Clay_Color){255, 255, 255, 255},
                    .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
         .backgroundColor = (Clay_Color){18, 18, 18, 255}}) {
      // Subtle center placeholder indicator
      CLAY_AUTO_ID(
          {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(16), .height = CLAY_SIZING_FIXED(16)}},
           .border = {
               .color = (Clay_Color){60, 60, 60, 255},
               .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
      }
    }

    // 2. Name badge (inverted white rectangle with black text)
    CLAY_AUTO_ID({.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                             .padding = {4, 4, 2, 2},
                             .childAlignment = {.x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER}},
                  .backgroundColor = (Clay_Color){255, 255, 255, 255}}) {
      Clay_String name_str = {
          .chars = name, .length = (int32_t)strlen(name), .isStaticallyAllocated = false};
      CLAY_TEXT(name_str, CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 11}));
    }

    // 3. Subtext / Version
    CLAY_AUTO_ID({.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                             .padding = {2, 2, 0, 0}}}) {
      Clay_String ver_str = {
          .chars = version, .length = (int32_t)strlen(version), .isStaticallyAllocated = false};
      CLAY_TEXT(ver_str, CLAY_TEXT_CONFIG({.textColor = {180, 180, 180, 255}, .fontSize = 10}));
    }
  }
}

void overview_render(OverviewState *state) {
  (void)state;

  // Overview / Library container
  CLAY(CLAY_ID("OverviewContent"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                   .padding = {20, 20, 20, 20},
                   .childGap = 16},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // 1. Header Box: [ LIBRARY // ]
    CLAY(CLAY_ID("LibraryHeaderBox"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                     .padding = {10, 12, 4, 4}},
          .border = {.color = (Clay_Color){255, 255, 255, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      CLAY_TEXT(CLAY_STRING("LIBRARY //"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 20}));
    }

    // 2. Toolbar Row: Search bar + New Group button
    CLAY(CLAY_ID("ToolbarRow"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(32)},
                     .childGap = 10,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
      // Search Bar Placeholder
      Clay_ElementId search_id = CLAY_ID("SearchBar");
      bool search_hover = Clay_PointerOver(search_id);

      CLAY(search_id,
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                       .padding = {10, 10, 4, 4},
                       .childGap = 8,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
            .border =
                {.color = search_hover ? (Clay_Color){255, 255, 255, 255}
                                       : (Clay_Color){160, 160, 160, 255},
                 .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
        ui_icon_search((Clay_Color){160, 160, 160, 255});
        CLAY_TEXT(CLAY_STRING("SEARCH..."),
                  CLAY_TEXT_CONFIG({.textColor = {130, 130, 130, 255}, .fontSize = 12}));
      }

      // New Group Button Placeholder
      Clay_ElementId new_group_id = CLAY_ID("NewGroupBtn");
      bool new_group_hover = Clay_PointerOver(new_group_id);

      CLAY(new_group_id,
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                       .padding = {12, 12, 4, 4},
                       .childGap = 8,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
            .border =
                {.color = new_group_hover ? (Clay_Color){255, 255, 255, 255}
                                          : (Clay_Color){120, 120, 120, 255},
                 .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor =
                new_group_hover ? (Clay_Color){45, 45, 45, 255} : (Clay_Color){25, 25, 25, 255}}) {
        ui_icon_plus((Clay_Color){200, 200, 200, 255});
        CLAY_TEXT(CLAY_STRING("NEW GROUP"),
                  CLAY_TEXT_CONFIG({.textColor = {200, 200, 200, 255}, .fontSize = 12}));
      }
    }

    // 3. Instances Grid (Wireframe Cards)
    CLAY(CLAY_ID("InstancesGrid"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                     .childGap = 14}}) {
      render_instance_card(CLAY_ID("InstanceCard1"), "INSTANCE_1", "VERSION 1.0.0");
      render_instance_card(CLAY_ID("InstanceCard2"), "INSTANCE_2", "VERSION 1.0.0");
    }
  }
}
