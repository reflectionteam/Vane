#pragma once

#include "ui/renderer/svg_loader.h"

typedef struct {
  char search_query[128];
  int active_filter;
} OverviewState;

void overview_init(OverviewState *state);
void overview_render(OverviewState *state, const SvgIconCache *icons);
