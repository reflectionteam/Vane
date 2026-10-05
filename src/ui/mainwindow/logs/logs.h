#pragma once

typedef struct {
  int dummy;
} LogsState;

void logs_init(LogsState *state);
void logs_render(LogsState *state);
