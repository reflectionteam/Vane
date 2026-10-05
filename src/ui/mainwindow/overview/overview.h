#pragma once

typedef struct {
  int dummy;
} OverviewState;

void overview_init(OverviewState *state);
void overview_render(OverviewState *state);
