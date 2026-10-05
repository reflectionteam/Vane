#include "ui/mainwindow/mainwindow.h"

#include <stdio.h>
#include <stdlib.h>

#include "ui/mainwindow/header/header.h"
#include "ui/mainwindow/sidebar/sidebar.h"

static void handle_clay_errors(Clay_ErrorData error_data) {
  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Clay Error: %s", error_data.errorText.chars);
}

static void main_window_draw_frame(MainWindow *win) {
  Uint64 now = SDL_GetTicks();
  float delta_time = (float)(now - win->last_time) / 1000.0f;
  if (delta_time <= 0.0f) {
    delta_time = 0.001f;
  }
  win->last_time = now;

  Clay_BeginLayout();

  CLAY(CLAY_ID("RootContainer"),
       {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                   .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
        .border = {.color = (Clay_Color){255, 255, 255, 255},
                   .width = {.left = 1, .right = 1, .top = 1, .bottom = 1, .betweenChildren = 0}},
        .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
    // Top: Header bar
    HeaderActions header_actions = header_render();
    if (header_actions.close_clicked) {
      win->running = false;
    }
    if (header_actions.minimize_clicked) {
      SDL_MinimizeWindow(win->window);
    }

    // Body: Split (Left: Sidebar, Right: Main content)
    CLAY(CLAY_ID("BodyContainer"),
         {.layout = {.layoutDirection = CLAY_LEFT_TO_RIGHT,
                     .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
          .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
      sidebar_render(&win->state);

      CLAY(CLAY_ID("MainContentArea"),
           {.layout = {.layoutDirection = CLAY_TOP_TO_BOTTOM,
                       .sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)}},
            .backgroundColor = (Clay_Color){0, 0, 0, 255}}) {
        switch (win->state.active_tab) {
        case TAB_OVERVIEW:
          overview_render(&win->overview_state);
          break;
        case TAB_MODS:
          mods_render(&win->mods_state);
          break;
        case TAB_SERVERS:
          servers_render(&win->servers_state);
          break;
        case TAB_SCREENSHOTS:
          screenshots_render(&win->screenshots_state);
          break;
        case TAB_LOGS:
          logs_render(&win->logs_state);
          break;
        default:
          break;
        }
      }
    }
  }

  Clay_RenderCommandArray commands = Clay_EndLayout(delta_time);

  SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
  SDL_RenderClear(win->renderer);

  clay_sdl3_render(&win->clay_sdl3, &commands);

  SDL_RenderPresent(win->renderer);
}

static void main_window_process_events(MainWindow *win) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      win->running = false;
      break;
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
    case SDL_EVENT_WINDOW_RESIZED: {
      SDL_GetWindowSize(win->window, &win->width, &win->height);
      Clay_SetLayoutDimensions((Clay_Dimensions){(float)win->width, (float)win->height});
      break;
    }
    case SDL_EVENT_MOUSE_WHEEL:
      Clay_UpdateScrollContainers(true, (Clay_Vector2){event.wheel.x, event.wheel.y}, 0.016f);
      break;
    default:
      break;
    }
  }

  float mouse_x = 0;
  float mouse_y = 0;
  Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
  Clay_SetPointerState((Clay_Vector2){mouse_x, mouse_y}, (buttons & SDL_BUTTON_LMASK) != 0);
}

bool main_window_init(MainWindow *win, const char *title, int width, int height) {
  if (!win) {
    return false;
  }

  win->width = width;
  win->height = height;
  win->running = false;
  win->last_time = 0;
  app_state_init(&win->state);
  overview_init(&win->overview_state);
  mods_init(&win->mods_state);
  servers_init(&win->servers_state);
  screenshots_init(&win->screenshots_state);
  logs_init(&win->logs_state);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init SDL: %s", SDL_GetError());
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

  win->window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
  if (!win->window) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return false;
  }

  win->renderer = SDL_CreateRenderer(win->window, NULL);
  if (!win->renderer) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(win->window);
    SDL_Quit();
    return false;
  }

  SDL_SetRenderVSync(win->renderer, 1);
  SDL_Log("Active renderer: %s", SDL_GetRendererName(win->renderer));

  char font_path[512] = {0};
  const char *base_path = SDL_GetBasePath();
  if (base_path) {
    snprintf(font_path, sizeof(font_path), "%sassets/fonts/GoogleSansCode-Regular.ttf", base_path);
  } else {
    snprintf(font_path, sizeof(font_path), "assets/fonts/GoogleSansCode-Regular.ttf");
  }

  if (!clay_sdl3_init(&win->clay_sdl3, win->renderer, font_path, 18.0f)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Clay SDL3 renderer");
    SDL_DestroyRenderer(win->renderer);
    SDL_DestroyWindow(win->window);
    SDL_Quit();
    return false;
  }

  Clay_SetMaxElementCount(1024);
  uint64_t total_memory_size = Clay_MinMemorySize();
  win->clay_memory =
      Clay_CreateArenaWithCapacityAndMemory(total_memory_size, malloc(total_memory_size));
  if (!win->clay_memory.memory) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate Clay memory arena");
    clay_sdl3_destroy(&win->clay_sdl3);
    SDL_DestroyRenderer(win->renderer);
    SDL_DestroyWindow(win->window);
    SDL_Quit();
    return false;
  }

  Clay_Initialize(
      win->clay_memory, (Clay_Dimensions){(float)width, (float)height},
      (Clay_ErrorHandler){.errorHandlerFunction = handle_clay_errors, .userData = NULL});
  Clay_SetMeasureTextFunction(clay_sdl3_measure_text, &win->clay_sdl3);

  win->last_time = SDL_GetTicks();
  win->running = true;

  return true;
}

void main_window_run(MainWindow *win) {
  if (!win || !win->running) {
    return;
  }

  while (win->running) {
    main_window_process_events(win);
    main_window_draw_frame(win);
  }
}

void main_window_destroy(MainWindow *win) {
  if (!win) {
    return;
  }

  clay_sdl3_destroy(&win->clay_sdl3);
  free(win->clay_memory.memory);
  win->clay_memory.memory = NULL;

  if (win->renderer) {
    SDL_DestroyRenderer(win->renderer);
    win->renderer = NULL;
  }

  if (win->window) {
    SDL_DestroyWindow(win->window);
    win->window = NULL;
  }

  SDL_Quit();
}
