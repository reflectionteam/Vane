#include "core/app_state.h"

void app_state_init(AppState *state) {
  if (!state) {
    return;
  }

  state->active_tab = TAB_1;
  state->click_count = 0;
}
