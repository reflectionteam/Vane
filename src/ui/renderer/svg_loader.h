#pragma once

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
  SDL_Texture *overview_white;
  SDL_Texture *overview_black;
  SDL_Texture *mods_white;
  SDL_Texture *mods_black;
  SDL_Texture *servers_white;
  SDL_Texture *servers_black;
  SDL_Texture *screenshots_white;
  SDL_Texture *screenshots_black;
  SDL_Texture *logs_white;
  SDL_Texture *logs_black;
  SDL_Texture *settings;
  SDL_Texture *logo;
  SDL_Texture *chevron_left;
  SDL_Texture *chevron_right;
  SDL_Texture *chevron_up;
} SvgIconCache;

typedef enum {
  SVG_COLOR_ORIGINAL = 0,
  SVG_COLOR_WHITE,
  SVG_COLOR_BLACK
} SvgColorMode;

bool svg_loader_init(SvgIconCache *cache, SDL_Renderer *renderer, const char *assets_base_path);
void svg_loader_destroy(SvgIconCache *cache);

SDL_Texture *svg_loader_render(SDL_Renderer *renderer, const char *filepath, int width, int height,
                               SvgColorMode color_mode);
