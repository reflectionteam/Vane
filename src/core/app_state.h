#pragma once

typedef enum { TAB_1 = 0, TAB_2, TAB_3, TAB_4, TAB_5, TAB_COUNT } AppTab;

typedef struct {
  int active_tab;
  int click_count;
} AppState;

void app_state_init(AppState *state);
