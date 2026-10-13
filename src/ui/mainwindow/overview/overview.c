#include "ui/mainwindow/overview/overview.h"

#include <clay.h>
#include <string.h>

void overview_init(OverviewState *state) {
  if (!state) {
    return;
  }
  memset(state->search_query, 0, sizeof(state->search_query));
  state->active_filter = 0;
  state->is_expanded = false;
  state->animation_progress = 0.0f;
}

void overview_handle_wheel(OverviewState *state, float wheel_y) {
  if (!state) {
    return;
  }
  if (wheel_y < -0.01f) {
    state->is_expanded = true;
  } else if (wheel_y > 0.01f) {
    state->is_expanded = false;
  }
}

static void render_recent_instances_card(const SvgIconCache *icons) {
  Clay_ElementId card_id = CLAY_ID("RecentInstancesCard");
  bool card_hover = Clay_PointerOver(card_id);

  CLAY(CLAY_ID("RecentInstancesContainer"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                   .childGap = 3}}) {
    // Header label
    CLAY(CLAY_ID("RecentInstancesLabel"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                     .padding = {6, 6, 2, 2}},
          .border = {.color = (Clay_Color){255, 255, 255, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 0, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      CLAY_TEXT(CLAY_STRING("RECENT INSTANCES"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 11}));
    }

    // Card content
    CLAY(card_id,
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIXED(230), .height = CLAY_SIZING_FIXED(46)},
                     .padding = {8, 10, 6, 6},
                     .childGap = 10,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
          .border = {.color = card_hover ? (Clay_Color){255, 255, 255, 255}
                                         : (Clay_Color){200, 200, 200, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor =
              card_hover ? (Clay_Color){28, 28, 28, 255} : (Clay_Color){0, 0, 0, 255}}) {
      // Instance square thumbnail placeholder
      CLAY(CLAY_ID("RecentInstanceThumb"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(30), .height = CLAY_SIZING_FIXED(30)}},
            .border = {.color = (Clay_Color){255, 255, 255, 255},
                       .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor = (Clay_Color){255, 255, 255, 255}}) {
      }

      // Instance text column
      CLAY(CLAY_ID("RecentInstanceTextCol"),
           {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                       .childGap = 2}}) {
        CLAY_TEXT(CLAY_STRING("NAME_"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 12}));
        CLAY_TEXT(CLAY_STRING("Fabric 1.21.4"),
                  CLAY_TEXT_CONFIG({.textColor = {170, 170, 170, 255}, .fontSize = 10}));
      }

      // Right Chevron
      if (icons && icons->chevron_right) {
        CLAY_AUTO_ID(
            {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(14),
                                   .height = CLAY_SIZING_FIXED(14)}},
             .image = {.imageData = icons->chevron_right}}) {
        }
      }
    }
  }
}

static void render_play_button(void) {
  Clay_ElementId outer_id = CLAY_ID("PlayButtonOuter");
  Clay_ElementId play_btn_id = CLAY_ID("PlayButton");
  bool play_hover = Clay_PointerOver(outer_id) || Clay_PointerOver(play_btn_id);

  Clay_Color bg = play_hover ? (Clay_Color){215, 215, 215, 255} : (Clay_Color){255, 255, 255, 255};
  Clay_Color text_col = (Clay_Color){0, 0, 0, 255};

  // Outer border frame with gap
  CLAY(outer_id,
       {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(172), .height = CLAY_SIZING_FIXED(46)},
                   .padding = {4, 4, 3, 3},
                   .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // Inner solid PLAY button
    CLAY(play_btn_id,
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                     .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
          .backgroundColor = bg}) {
      CLAY_TEXT(CLAY_STRING("PLAY"),
                CLAY_TEXT_CONFIG({.textColor = text_col, .fontSize = 18}));
    }
  }
}

static void render_recent_servers_card(const SvgIconCache *icons) {
  Clay_ElementId card_id = CLAY_ID("RecentServersCard");
  bool card_hover = Clay_PointerOver(card_id);

  CLAY(CLAY_ID("RecentServersContainer"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                   .childAlignment = {.x = CLAY_ALIGN_X_RIGHT},
                   .childGap = 3}}) {
    // Header label
    CLAY(CLAY_ID("RecentServersLabel"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                     .padding = {6, 6, 2, 2}},
          .border = {.color = (Clay_Color){255, 255, 255, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 0, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      CLAY_TEXT(CLAY_STRING("RECENT SERVERS"),
                CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 11}));
    }

    // Card content
    CLAY(card_id,
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIXED(230), .height = CLAY_SIZING_FIXED(46)},
                     .padding = {8, 10, 6, 6},
                     .childGap = 10,
                     .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
          .border = {.color = card_hover ? (Clay_Color){255, 255, 255, 255}
                                         : (Clay_Color){200, 200, 200, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor =
              card_hover ? (Clay_Color){28, 28, 28, 255} : (Clay_Color){0, 0, 0, 255}}) {
      // Left Chevron
      if (icons && icons->chevron_left) {
        CLAY_AUTO_ID(
            {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(14),
                                   .height = CLAY_SIZING_FIXED(14)}},
             .image = {.imageData = icons->chevron_left}}) {
        }
      }

      // Server text column (aligned right)
      CLAY(CLAY_ID("RecentServerTextCol"),
           {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                       .childAlignment = {.x = CLAY_ALIGN_X_RIGHT},
                       .childGap = 2}}) {
        CLAY_TEXT(CLAY_STRING("NAME_Server"),
                  CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 12}));
        CLAY_TEXT(CLAY_STRING("Fabric 1.21.4"),
                  CLAY_TEXT_CONFIG({.textColor = {170, 170, 170, 255}, .fontSize = 10}));
      }

      // Server square thumbnail placeholder
      CLAY(CLAY_ID("RecentServerThumb"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(30), .height = CLAY_SIZING_FIXED(30)}},
            .border = {.color = (Clay_Color){120, 120, 120, 255},
                       .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
            .backgroundColor = (Clay_Color){60, 60, 60, 255}}) {
      }
    }
  }
}

static void render_library_instance_card(int index, const char *name,
                                         const char *version, float anim) {
  Clay_ElementId card_id = CLAY_IDI("LibraryCard", index);
  bool card_hover = Clay_PointerOver(card_id);
  uint8_t border_val = (uint8_t)(75.0f + (255.0f - 75.0f) * anim);
  uint8_t current_border = card_hover ? 255 : border_val;
  uint8_t badge_val = (uint8_t)(143.0f + (255.0f - 143.0f) * anim);

  CLAY(card_id,
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(130), .height = CLAY_SIZING_FIXED(180)},
                   .padding = {6, 6, 6, 6},
                   .childGap = 5},
        .border = {.color = (Clay_Color){current_border, current_border, current_border, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = card_hover ? (Clay_Color){18, 18, 18, 255} : (Clay_Color){0, 0, 0, 255}}) {
    // 1. Image / Thumbnail template placeholder (clean bordered slot, no image as requested)
    CLAY(CLAY_IDI("InstanceThumb", index),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(104)}},
          .border = {.color = (Clay_Color){current_border, current_border, current_border, 255},
                     .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
          .backgroundColor = (Clay_Color){22, 22, 22, 255}}) {
    }

    // 2. Name badge: aligned text baseline to bottom edge of frame
    CLAY(CLAY_IDI("InstanceNameBadge", index),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIXED(11)},
                     .padding = {.left = 0, .right = 6, .top = 0, .bottom = 0}},
          .backgroundColor = (Clay_Color){badge_val, badge_val, badge_val, 255}}) {
      Clay_String name_str = (Clay_String){
          .chars = name ? name : "name_instance",
          .length = (int32_t)strlen(name ? name : "name_instance"),
          .isStaticallyAllocated = false,
      };
      CLAY_TEXT(name_str,
                CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 11}));
    }

    // 3. Version badge: aligned text baseline to bottom edge of frame
    CLAY(CLAY_IDI("InstanceVerBadge", index),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIXED(10)},
                     .padding = {.left = 0, .right = 4, .top = 0, .bottom = 0}},
          .backgroundColor = (Clay_Color){badge_val, badge_val, badge_val, 255}}) {
      Clay_String ver_str = (Clay_String){
          .chars = version ? version : "Fabric 1.21.4",
          .length = (int32_t)strlen(version ? version : "Fabric 1.21.4"),
          .isStaticallyAllocated = false,
      };
      CLAY_TEXT(ver_str,
                CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 10}));
    }
  }
}

void overview_render(OverviewState *state, const SvgIconCache *icons, float delta_time) {
  Clay_PointerData pointer = Clay_GetPointerState();

  if (state) {
    float target = state->is_expanded ? 1.0f : 0.0f;
    float step = delta_time * 12.0f;
    if (step > 1.0f) {
      step = 1.0f;
    }
    state->animation_progress += (target - state->animation_progress) * step;
    float diff = target - state->animation_progress;
    if (diff < 0.0f) {
      diff = -diff;
    }
    if (diff < 0.001f) {
      state->animation_progress = target;
    }
    if (state->animation_progress < 0.0f) state->animation_progress = 0.0f;
    if (state->animation_progress > 1.0f) state->animation_progress = 1.0f;
  }

  float anim = state ? state->animation_progress : 0.0f;
  float top_percent = 0.5f * (1.0f - anim);

  // Main Overview Container
  CLAY(CLAY_ID("OverviewContent"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // 1. Top Section: Banner slot + Quick Launch Action Bar (50% in standard view, animates to 0% on full expansion)
    if (top_percent > 0.001f) {
      CLAY(CLAY_ID("OverviewTopSection"),
           {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_PERCENT(top_percent)}},
            .clip = {.vertical = true}}) {
        // Geometric banner placeholder (no real Minecraft cover as requested)
        CLAY(CLAY_ID("BannerContainer"),
             {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
              .backgroundColor = (Clay_Color){12, 12, 12, 255}}) {
        }

        // Quick Launch Bar: RECENT INSTANCES + PLAY + RECENT SERVERS
        CLAY(CLAY_ID("QuickLaunchBar"),
             {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                         .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                         .padding = {16, 16, 10, 10},
                         .childAlignment = {.y = CLAY_ALIGN_Y_BOTTOM}}}) {
          render_recent_instances_card(icons);

          CLAY(CLAY_ID("QuickLaunchSpacerLeft"),
               {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}}}) {
          }

          render_play_button();

          CLAY(CLAY_ID("QuickLaunchSpacerRight"),
               {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}}}) {
          }

          render_recent_servers_card(icons);
        }
      }
    }

    // 2. Horizontal Divider
    Clay_ElementId divider_id = CLAY_ID("OverviewSectionDivider");
    bool divider_hover = Clay_PointerOver(divider_id);
    if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME && divider_hover && state) {
      state->is_expanded = !state->is_expanded;
    }

    if (anim < 0.999f) {
      CLAY(divider_id,
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(1)}},
            .backgroundColor = divider_hover ? (Clay_Color){255, 255, 255, 255}
                                             : (Clay_Color){200, 200, 200, 255}}) {
      }
    }

    // 3. Library Section: LIBRARY // + Search Toolbar + Filter Pills + Cards Grid
    CLAY(CLAY_ID("LibrarySection"),
         {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                     .padding = {16, 16, 16, 16},
                     .childGap = 12}}) {
      // 3.1 Header badge [ LIBRARY // ]: gray (143) in normal view, transitions to white (255) on fullscreen
      uint8_t badge_val = (uint8_t)(143.0f + (255.0f - 143.0f) * anim);
      CLAY(CLAY_ID("LibraryHeaderBadge"),
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIXED(22)},
                       .padding = {.left = 0, .right = 14, .top = 0, .bottom = 0}},
            .backgroundColor = (Clay_Color){badge_val, badge_val, badge_val, 255}}) {
        CLAY_TEXT(CLAY_STRING("LIBRARY //"),
                  CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 22}));
      }

      // 3.2 Toolbar: Search Bar + "+  NEW GROUP" Button
      CLAY(CLAY_ID("LibraryToolbarRow"),
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(32)},
                       .childGap = 10,
                       .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}}}) {
        // Search bar with animated border (gray in split view, white in fullscreen)
        Clay_ElementId search_id = CLAY_ID("LibrarySearchBar");
        bool search_hover = Clay_PointerOver(search_id);
        uint8_t search_border_val = (uint8_t)(100.0f + (255.0f - 100.0f) * anim);
        uint8_t current_search_border = search_hover ? 255 : search_border_val;

        CLAY(search_id,
             {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                         .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                         .padding = {10, 10, 0, 0},
                         .childGap = 8,
                         .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}},
              .border = {.color = (Clay_Color){current_search_border, current_search_border, current_search_border, 255},
                         .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
              .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
          // Search icon
          if (icons && icons->search) {
            CLAY_AUTO_ID(
                {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(14),
                                       .height = CLAY_SIZING_FIXED(14)}},
                 .image = {.imageData = icons->search}}) {
            }
          }

          // Search placeholder or query
          if (state && state->search_query[0] != '\0') {
            Clay_String query_str = (Clay_String){
                .chars = state->search_query,
                .length = (int32_t)strlen(state->search_query),
                .isStaticallyAllocated = false,
            };
            CLAY_TEXT(query_str,
                      CLAY_TEXT_CONFIG({.textColor = {255, 255, 255, 255}, .fontSize = 12}));
          } else {
            CLAY_TEXT(CLAY_STRING("SEARCH..."),
                      CLAY_TEXT_CONFIG({.textColor = {102, 102, 102, 255}, .fontSize = 12}));
          }
        }

        // "+  NEW GROUP" Button: transitions accent from gray (84) to white (255) on fullscreen
        Clay_ElementId new_group_id = CLAY_ID("LibraryNewGroupBtn");
        bool new_group_hover = Clay_PointerOver(new_group_id);
        uint8_t btn_val = (uint8_t)(84.0f + (255.0f - 84.0f) * anim);
        uint8_t btn_hover_val = (uint8_t)(105.0f + (230.0f - 105.0f) * anim);
        uint8_t current_btn_bg = new_group_hover ? btn_hover_val : btn_val;

        CLAY(new_group_id,
             {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                         .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_GROW(0)},
                         .padding = {14, 14, 0, 0},
                         .childGap = 8,
                         .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
              .backgroundColor = (Clay_Color){current_btn_bg, current_btn_bg, current_btn_bg, 255}}) {
          CLAY_TEXT(CLAY_STRING("+"),
                    CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 14}));
          CLAY_TEXT(CLAY_STRING("NEW GROUP"),
                    CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255}, .fontSize = 12}));
        }
      }

      // 3.3 Cards Grid: Instance template matching mockup
      CLAY(CLAY_ID("LibraryCardsGrid"),
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                       .childGap = 12}}) {
        render_library_instance_card(0, "name_instance", "Fabric 1.21.4", anim);
      }
    }
  }
}
