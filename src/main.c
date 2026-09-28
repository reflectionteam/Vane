#include <SDL3/SDL.h>
#include <clay.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ui/renderer/clay_sdl3.h"
#include "ui/styles/button_style.h"
#include "ui/widgets/button.h"

static void HandleClayErrors(Clay_ErrorData error_data) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Clay Error: %s", error_data.errorText.chars);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init SDL: %s", SDL_GetError());
        return 1;
    }

    int width = 800;
    int height = 600;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    SDL_Window *window = SDL_CreateWindow("Vane", width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderVSync(renderer, 1);
    SDL_Log("Active renderer: %s", SDL_GetRendererName(renderer));

    // Initialize Clay SDL3 renderer & TTF
    Clay_SDL3Context clay_sdl3 = {0};
    char font_path[512] = {0};
    const char *base_path = SDL_GetBasePath();
    if (base_path) {
        snprintf(font_path, sizeof(font_path), "%sassets/fonts/Roboto-Regular.ttf", base_path);
    } else {
        snprintf(font_path, sizeof(font_path), "assets/fonts/Roboto-Regular.ttf");
    }

    if (!Clay_SDL3_Init(&clay_sdl3, renderer, font_path, 18.0f)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Clay SDL3 renderer");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize Clay with 1024 elements (drops memory footprint from 5.5MB to 0.75MB)
    Clay_SetMaxElementCount(1024);
    uint64_t total_memory_size = Clay_MinMemorySize();
    Clay_Arena clay_memory = Clay_CreateArenaWithCapacityAndMemory(total_memory_size, malloc(total_memory_size));
    if (!clay_memory.memory) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate Clay memory arena");
        Clay_SDL3_Destroy(&clay_sdl3);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Clay_Initialize(clay_memory, (Clay_Dimensions){ (float)width, (float)height }, (Clay_ErrorHandler){ HandleClayErrors });
    Clay_SetMeasureTextFunction(Clay_SDL3_MeasureText, &clay_sdl3);

    bool running = true;
    SDL_Event event;
    int click_count = 0;
    Uint64 last_time = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                case SDL_EVENT_WINDOW_RESIZED: {
                    SDL_GetWindowSize(window, &width, &height);
                    Clay_SetLayoutDimensions((Clay_Dimensions){ (float)width, (float)height });
                    break;
                }
                case SDL_EVENT_MOUSE_WHEEL:
                    Clay_UpdateScrollContainers(true, (Clay_Vector2){ event.wheel.x, event.wheel.y }, 0.016f);
                    break;
                default:
                    break;
            }
        }

        float mouse_x, mouse_y;
        Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        Clay_SetPointerState(
            (Clay_Vector2){ mouse_x, mouse_y },
            (buttons & SDL_BUTTON_LMASK) != 0
        );

        Clay_BeginLayout();

        CLAY(CLAY_ID("RootContainer"), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_GROW(0)
                },
                .childAlignment = {
                    .x = CLAY_ALIGN_X_CENTER,
                    .y = CLAY_ALIGN_Y_CENTER
                },
                .childGap = 16
            },
            .backgroundColor = (Clay_Color){ 18, 18, 20, 255 }
        }) {
            char btn_text[64];
            if (click_count == 0) {
                snprintf(btn_text, sizeof(btn_text), "Нажми меня");
            } else {
                snprintf(btn_text, sizeof(btn_text), "Нажато %d раз!", click_count);
            }

            if (UI_Button(CLAY_ID("DemoButton"), btn_text, &BUTTON_PRIMARY)) {
                click_count++;
                SDL_Log("Кнопка нажата! Всего кликов: %d", click_count);
            }
        }

        Uint64 now = SDL_GetTicks();
        float delta_time = (float)(now - last_time) / 1000.0f;
        if (delta_time <= 0.0f) delta_time = 0.001f;
        last_time = now;

        Clay_RenderCommandArray commands = Clay_EndLayout(delta_time);

        SDL_SetRenderDrawColor(renderer, 18, 18, 20, 255);
        SDL_RenderClear(renderer);

        Clay_SDL3_Render(&clay_sdl3, &commands);

        SDL_RenderPresent(renderer);
    }

    Clay_SDL3_Destroy(&clay_sdl3);
    free(clay_memory.memory);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
