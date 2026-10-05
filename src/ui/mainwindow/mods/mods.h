#pragma once

typedef struct {
  int dummy;
} ModsState;

void mods_init(ModsState *state);
void mods_render(ModsState *state);
