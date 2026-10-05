#pragma once

typedef enum {
  TAB_OVERVIEW = 0,
  TAB_MODS,
  TAB_SERVERS,
  TAB_SCREENSHOTS,
  TAB_LOGS,
  TAB_COUNT
} AppTab;

typedef struct {
  AppTab active_tab;
} AppState;

void app_state_init(AppState *state);
