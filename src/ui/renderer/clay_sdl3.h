#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <clay.h>
#include <stdbool.h>

typedef struct {
  SDL_Renderer *renderer;
  TTF_TextEngine *text_engine;
  TTF_Font **fonts;
  size_t font_count;
} Clay_SDL3Context;

bool clay_sdl3_init(Clay_SDL3Context *ctx, SDL_Renderer *renderer, const char *font_path,
                    float default_font_size);
void clay_sdl3_destroy(Clay_SDL3Context *ctx);
Clay_Dimensions clay_sdl3_measure_text(Clay_StringSlice text, Clay_TextElementConfig *config,
                                       void *user_data);
void clay_sdl3_render(Clay_SDL3Context *ctx, Clay_RenderCommandArray *commands);
