#pragma once

#include <stdbool.h>

typedef struct {
  bool minimize_clicked;
  bool close_clicked;
  bool settings_clicked;
} HeaderActions;

HeaderActions header_render(void);
