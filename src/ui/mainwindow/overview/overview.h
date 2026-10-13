#pragma once

#include <stdbool.h>
#include "ui/renderer/svg_loader.h"

typedef struct {
  char search_query[128];
  int active_filter;
  bool is_expanded;
  float animation_progress;
} OverviewState;

void overview_init(OverviewState *state);
void overview_handle_wheel(OverviewState *state, float wheel_y);
void overview_render(OverviewState *state, const SvgIconCache *icons, float delta_time);
