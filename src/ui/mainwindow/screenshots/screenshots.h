#pragma once

typedef struct {
  int dummy;
} ScreenshotsState;

void screenshots_init(ScreenshotsState *state);
void screenshots_render(ScreenshotsState *state);
