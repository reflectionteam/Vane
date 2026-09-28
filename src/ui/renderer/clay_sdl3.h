#pragma once

#include <clay.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

typedef struct {
    SDL_Renderer *renderer;
    TTF_TextEngine *text_engine;
    TTF_Font **fonts;
    size_t font_count;
} Clay_SDL3Context;

bool Clay_SDL3_Init(Clay_SDL3Context *ctx, SDL_Renderer *renderer, const char *font_path, float default_font_size);
void Clay_SDL3_Destroy(Clay_SDL3Context *ctx);
Clay_Dimensions Clay_SDL3_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *user_data);
void Clay_SDL3_Render(Clay_SDL3Context *ctx, Clay_RenderCommandArray *commands);
