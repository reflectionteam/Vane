#include "ui/widgets/icon/icons.h"

void ui_icon_logo_slot(Clay_Color color) {
  CLAY(
      CLAY_ID("LogoSlotIcon"),
      {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                  .sizing = {.width = CLAY_SIZING_FIXED(20), .height = CLAY_SIZING_FIXED(20)},
                  .padding = {2, 2, 2, 2},
                  .childGap = 2},
       .border = {.color = color,
                  .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    CLAY(CLAY_ID("LogoSlotBar1"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(6), .height = CLAY_SIZING_FIXED(3)}},
          .backgroundColor = color}) {
    }
    CLAY(CLAY_ID("LogoSlotBar2"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(11), .height = CLAY_SIZING_FIXED(3)}},
          .backgroundColor = color}) {
    }
    CLAY(CLAY_ID("LogoSlotBar3"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(16), .height = CLAY_SIZING_FIXED(3)}},
          .backgroundColor = color}) {
    }
  }
}

void ui_icon_overview(Clay_Color color) {
  CLAY(
      CLAY_ID("IconOverview"),
      {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                  .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(14)},
                  .childGap = 2},
       .border = {.color = color,
                  .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    CLAY(CLAY_ID("IconOverviewRow1"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(5)},
                     .childGap = 2}}) {
      CLAY(CLAY_ID("IconOverviewCell1"),
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = color}) {
      }
      CLAY(CLAY_ID("IconOverviewCell2"),
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .border = {
                .color = color,
                .width = {.left = 1, .right = 0, .top = 0, .bottom = 0, .betweenChildren = 0}}}) {
      }
    }
    CLAY(CLAY_ID("IconOverviewRow2"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
                     .childGap = 2}}) {
      CLAY(CLAY_ID("IconOverviewCell3"),
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .border = {
                .color = color,
                .width = {.left = 0, .right = 0, .top = 1, .bottom = 0, .betweenChildren = 0}}}) {
      }
      CLAY(CLAY_ID("IconOverviewCell4"),
           {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = color}) {
      }
    }
  }
}

void ui_icon_mods(Clay_Color color) {
  CLAY(
      CLAY_ID("IconMods"),
      {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                  .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(14)},
                  .padding = {2, 2, 2, 2},
                  .childGap = 2},
       .border = {.color = color,
                  .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    CLAY(CLAY_ID("IconModsInnerTop"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(3)}},
          .border = {
              .color = color,
              .width = {.left = 0, .right = 0, .top = 0, .bottom = 1, .betweenChildren = 0}}}) {
    }
    CLAY(CLAY_ID("IconModsInnerBot"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(4), .height = CLAY_SIZING_FIXED(3)}},
          .backgroundColor = color}) {
    }
  }
}

void ui_icon_servers(Clay_Color color) {
  CLAY(CLAY_ID("IconServers"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(14)},
                   .childGap = 2}}) {
    CLAY(CLAY_ID("IconServersRack1"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(6)},
                     .padding = {2, 2, 1, 1},
                     .childAlignment = {.x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_CENTER}},
          .border = {
              .color = color,
              .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
      CLAY(CLAY_ID("IconServersDot1"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(2), .height = CLAY_SIZING_FIXED(2)}},
            .backgroundColor = color}) {
      }
    }
    CLAY(CLAY_ID("IconServersRack2"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(6)},
                     .padding = {2, 2, 1, 1},
                     .childAlignment = {.x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_CENTER}},
          .border = {
              .color = color,
              .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
      CLAY(CLAY_ID("IconServersDot2"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(2), .height = CLAY_SIZING_FIXED(2)}},
            .backgroundColor = color}) {
      }
    }
  }
}

void ui_icon_screenshots(Clay_Color color) {
  CLAY(
      CLAY_ID("IconScreenshots"),
      {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                  .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(14)},
                  .padding = {2, 2, 2, 2},
                  .childAlignment = {.x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_BOTTOM}},
       .border = {.color = color,
                  .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    CLAY(CLAY_ID("IconScreenshotsInner"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(6), .height = CLAY_SIZING_FIXED(5)}},
          .border = {
              .color = color,
              .width = {.left = 1, .right = 0, .top = 1, .bottom = 0, .betweenChildren = 0}}}) {
    }
  }
}

void ui_icon_logs(Clay_Color color) {
  CLAY(
      CLAY_ID("IconLogs"),
      {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                  .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(14)},
                  .padding = {1, 1, 2, 2},
                  .childGap = 2},
       .border = {.color = color,
                  .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    CLAY(CLAY_ID("IconLogsLine1"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(1)}},
          .backgroundColor = color}) {
    }
    CLAY(CLAY_ID("IconLogsLine2"),
         {.layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(1)}},
          .backgroundColor = color}) {
    }
    CLAY(CLAY_ID("IconLogsLine3"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(6), .height = CLAY_SIZING_FIXED(1)}},
          .backgroundColor = color}) {
    }
  }
}

void ui_icon_settings(Clay_Color color) {
  CLAY(CLAY_ID("IconSettings"),
       {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                   .sizing = {.width = CLAY_SIZING_FIXED(14), .height = CLAY_SIZING_FIXED(12)},
                   .childGap = 4,
                   .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}}}) {
    CLAY(CLAY_ID("IconSettingsCol1"),
         {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {.width = CLAY_SIZING_FIXED(4), .height = CLAY_SIZING_GROW(0)},
                     .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_TOP}}}) {
      CLAY(CLAY_ID("IconSettingsTrack1"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(1), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = color}) {
      }
    }
    CLAY(CLAY_ID("IconSettingsCol2"),
         {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                     .sizing = {.width = CLAY_SIZING_FIXED(4), .height = CLAY_SIZING_GROW(0)},
                     .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_BOTTOM}}}) {
      CLAY(CLAY_ID("IconSettingsTrack2"),
           {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(1), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = color}) {
      }
    }
  }
}

void ui_icon_search(Clay_Color color) {
  CLAY(CLAY_ID("IconSearch"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(12), .height = CLAY_SIZING_FIXED(12)},
                   .childAlignment = {.x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_BOTTOM}}}) {
    CLAY(CLAY_ID("IconSearchRing"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(9), .height = CLAY_SIZING_FIXED(9)}},
          .border = {
              .color = color,
              .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}}}) {
    }
    CLAY(CLAY_ID("IconSearchStem"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(4), .height = CLAY_SIZING_FIXED(1)}},
          .backgroundColor = color}) {
    }
  }
}

void ui_icon_plus(Clay_Color color) {
  CLAY(CLAY_ID("IconPlus"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_FIXED(10), .height = CLAY_SIZING_FIXED(10)},
                   .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}}}) {
    CLAY(CLAY_ID("IconPlusH"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(10), .height = CLAY_SIZING_FIXED(2)}},
          .backgroundColor = color}) {
    }
    CLAY(CLAY_ID("IconPlusV"),
         {.layout = {.sizing = {.width = CLAY_SIZING_FIXED(2), .height = CLAY_SIZING_FIXED(8)}},
          .backgroundColor = color}) {
    }
  }
}
