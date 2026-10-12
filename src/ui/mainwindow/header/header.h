#pragma once

#include <stdbool.h>

#include "ui/renderer/svg_loader.h"

typedef struct {
  bool minimize_clicked;
  bool close_clicked;
  bool settings_clicked;
} HeaderActions;

HeaderActions header_render(const SvgIconCache *icons);
