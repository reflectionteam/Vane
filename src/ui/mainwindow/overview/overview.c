#include "ui/mainwindow/overview/overview.h"

#include <clay.h>
#include <string.h>

void overview_init(OverviewState *state) {
  if (!state) {
    return;
  }
  memset(state->search_query, 0, sizeof(state->search_query));
  state->active_filter = 0;
}

static void render_recent_instances_card(const SvgIconCache *icons) {
  Clay_ElementId card_id = CLAY_ID("RecentInstancesCard");
  bool card_hover = Clay_PointerOver(card_id);

  CLAY(CLAY_ID("RecentInstancesContainer"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                   .childGap = 4}}) {
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
              card_hover ? (Clay_Color){25, 25, 25, 255} : (Clay_Color){0, 0, 0, 255}}) {
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
  Clay_ElementId play_btn_id = CLAY_ID("PlayButton");
  bool play_hover = Clay_PointerOver(play_btn_id);

  Clay_Color bg = play_hover ? (Clay_Color){220, 220, 220, 255} : (Clay_Color){255, 255, 255, 255};
  Clay_Color text_col = (Clay_Color){0, 0, 0, 255};

  CLAY(play_btn_id,
       {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(190), .height = CLAY_SIZING_FIXED(48)},
                   .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 2, .right = 2, .top = 2, .bottom = 2, .betweenChildren = 0}},
        .backgroundColor = bg}) {
    CLAY_TEXT(CLAY_STRING("PLAY"),
              CLAY_TEXT_CONFIG({.textColor = text_col, .fontSize = 20}));
  }
}

static void render_recent_servers_card(const SvgIconCache *icons) {
  Clay_ElementId card_id = CLAY_ID("RecentServersCard");
  bool card_hover = Clay_PointerOver(card_id);

  CLAY(CLAY_ID("RecentServersContainer"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
                   .childAlignment = {.x = CLAY_ALIGN_X_RIGHT},
                   .childGap = 4}}) {
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
              card_hover ? (Clay_Color){25, 25, 25, 255} : (Clay_Color){0, 0, 0, 255}}) {
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

void overview_render(OverviewState *state, const SvgIconCache *icons) {
  (void)state;

  // Main Overview Container
  CLAY(CLAY_ID("OverviewContent"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // 1. Top Section: Banner slot + Quick Launch Action Bar
    CLAY(CLAY_ID("OverviewTopSection"),
         {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(240)}}}) {
      // Geometric banner placeholder (no real Minecraft cover as requested)
      CLAY(CLAY_ID("BannerContainer"),
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = (Clay_Color){14, 14, 14, 255}}) {
      }

      // Quick Launch Bar: RECENT INSTANCES + PLAY + RECENT SERVERS
      CLAY(CLAY_ID("QuickLaunchBar"),
           {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0)},
                       .padding = {16, 16, 8, 8},
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

    // 2. Horizontal Divider
    CLAY(CLAY_ID("OverviewSectionDivider"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(1)}},
          .backgroundColor = (Clay_Color){255, 255, 255, 255}}) {
    }
  }
}
