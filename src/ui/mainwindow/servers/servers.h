#pragma once

typedef struct {
  int dummy;
} ServersState;

void servers_init(ServersState *state);
void servers_render(ServersState *state);
