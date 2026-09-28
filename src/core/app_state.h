#pragma once

typedef enum { TAB_OVERVIEW = 0, TAB_PROJECTS, TAB_SETTINGS, TAB_COUNT } AppTab;

typedef struct {
  AppTab active_tab;
  int click_count;
} AppState;

void app_state_init(AppState *state);
