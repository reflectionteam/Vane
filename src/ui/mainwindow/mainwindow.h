#pragma once

#include <SDL3/SDL.h>
#include <clay.h>
#include <stdbool.h>

#include "core/app_state.h"
#include "ui/mainwindow/logs/logs.h"
#include "ui/mainwindow/mods/mods.h"
#include "ui/mainwindow/overview/overview.h"
#include "ui/mainwindow/screenshots/screenshots.h"
#include "ui/mainwindow/servers/servers.h"
#include "ui/renderer/clay_sdl3.h"

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Clay_SDL3Context clay_sdl3;
  Clay_Arena clay_memory;
  int width;
  int height;
  bool running;
  Uint64 last_time;

  AppState state;
  OverviewState overview_state;
  ModsState mods_state;
  ServersState servers_state;
  ScreenshotsState screenshots_state;
  LogsState logs_state;
} MainWindow;

bool main_window_init(MainWindow *win, const char *title, int width, int height);
void main_window_run(MainWindow *win);
void main_window_destroy(MainWindow *win);
