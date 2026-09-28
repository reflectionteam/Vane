#include "ui/renderer/clay_sdl3.h"
#include <stdlib.h>
#include <math.h>

static const int NUM_CIRCLE_SEGMENTS = 16;

static void SDL_Clay_RenderFillRoundedRect(SDL_Renderer *renderer, const SDL_FRect rect, const float cornerRadius, const Clay_Color _color) {
    const SDL_FColor color = { _color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f, _color.a / 255.0f };

    int indexCount = 0, vertexCount = 0;

    const float minRadius = SDL_min(rect.w, rect.h) / 2.0f;
    const float clampedRadius = SDL_min(cornerRadius, minRadius);
    const int numCircleSegments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(clampedRadius * 0.5f));

    const int totalVertices = 4 + (4 * (numCircleSegments * 2)) + 2 * 4;
    const int totalIndices = 6 + (4 * (numCircleSegments * 3)) + 6 * 4;

    SDL_Vertex vertices[totalVertices];
    int indices[totalIndices];

    // Center rectangle
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + clampedRadius}, color, {0, 0} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + clampedRadius}, color, {1, 0} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + rect.h - clampedRadius}, color, {1, 1} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + rect.h - clampedRadius}, color, {0, 1} };

    indices[indexCount++] = 0;
    indices[indexCount++] = 1;
    indices[indexCount++] = 3;
    indices[indexCount++] = 1;
    indices[indexCount++] = 2;
    indices[indexCount++] = 3;

    // Rounded corners
    const float step = (SDL_PI_F / 2.0f) / numCircleSegments;
    for (int i = 0; i < numCircleSegments; i++) {
        const float angle1 = (float)i * step;
        const float angle2 = ((float)i + 1.0f) * step;

        for (int j = 0; j < 4; j++) {
            float cx, cy, signX, signY;
            switch (j) {
                case 0: cx = rect.x + clampedRadius; cy = rect.y + clampedRadius; signX = -1; signY = -1; break;
                case 1: cx = rect.x + rect.w - clampedRadius; cy = rect.y + clampedRadius; signX = 1; signY = -1; break;
                case 2: cx = rect.x + rect.w - clampedRadius; cy = rect.y + rect.h - clampedRadius; signX = 1; signY = 1; break;
                case 3: cx = rect.x + clampedRadius; cy = rect.y + rect.h - clampedRadius; signX = -1; signY = 1; break;
                default:
                    SDL_free(vertices);
                    SDL_free(indices);
                    return;
            }

            vertices[vertexCount++] = (SDL_Vertex){ {cx + SDL_cosf(angle1) * clampedRadius * signX, cy + SDL_sinf(angle1) * clampedRadius * signY}, color, {0, 0} };
            vertices[vertexCount++] = (SDL_Vertex){ {cx + SDL_cosf(angle2) * clampedRadius * signX, cy + SDL_sinf(angle2) * clampedRadius * signY}, color, {0, 0} };

            indices[indexCount++] = j;
            indices[indexCount++] = vertexCount - 2;
            indices[indexCount++] = vertexCount - 1;
        }
    }

    // Top edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y}, color, {0, 0} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y}, color, {1, 0} };
    indices[indexCount++] = 0;
    indices[indexCount++] = vertexCount - 2;
    indices[indexCount++] = vertexCount - 1;
    indices[indexCount++] = 1;
    indices[indexCount++] = 0;
    indices[indexCount++] = vertexCount - 1;

    // Right edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w, rect.y + clampedRadius}, color, {1, 0} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w, rect.y + rect.h - clampedRadius}, color, {1, 1} };
    indices[indexCount++] = 1;
    indices[indexCount++] = vertexCount - 2;
    indices[indexCount++] = vertexCount - 1;
    indices[indexCount++] = 2;
    indices[indexCount++] = 1;
    indices[indexCount++] = vertexCount - 1;

    // Bottom edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + rect.h}, color, {1, 1} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + rect.h}, color, {0, 1} };
    indices[indexCount++] = 2;
    indices[indexCount++] = vertexCount - 2;
    indices[indexCount++] = vertexCount - 1;
    indices[indexCount++] = 3;
    indices[indexCount++] = 2;
    indices[indexCount++] = vertexCount - 1;

    // Left edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x, rect.y + rect.h - clampedRadius}, color, {0, 1} };
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x, rect.y + clampedRadius}, color, {0, 0} };
    indices[indexCount++] = 3;
    indices[indexCount++] = vertexCount - 2;
    indices[indexCount++] = vertexCount - 1;
    indices[indexCount++] = 0;
    indices[indexCount++] = 3;
    indices[indexCount++] = vertexCount - 1;

    SDL_RenderGeometry(renderer, NULL, vertices, vertexCount, indices, indexCount);
}

static void SDL_Clay_RenderArc(SDL_Renderer *renderer, const SDL_FPoint center, const float radius, const float startAngle, const float endAngle, const float thickness, const Clay_Color color) {
    SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a);

    const float radStart = startAngle * (SDL_PI_F / 180.0f);
    const float radEnd = endAngle * (SDL_PI_F / 180.0f);
    const int numCircleSegments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(radius * 1.5f));
    const float angleStep = (radEnd - radStart) / (float)numCircleSegments;
    const float thicknessStep = 0.4f;

    for (float t = thicknessStep; t < thickness - thicknessStep; t += thicknessStep) {
        SDL_FPoint points[numCircleSegments + 1];
        const float clampedRadius = SDL_max(radius - t, 1.0f);

        for (int i = 0; i <= numCircleSegments; i++) {
            const float angle = radStart + i * angleStep;
            points[i] = (SDL_FPoint){
                SDL_roundf(center.x + SDL_cosf(angle) * clampedRadius),
                SDL_roundf(center.y + SDL_sinf(angle) * clampedRadius)
            };
        }
        SDL_RenderLines(renderer, points, numCircleSegments + 1);
    }
}

bool Clay_SDL3_Init(Clay_SDL3Context *ctx, SDL_Renderer *renderer, const char *font_path, float default_font_size) {
    if (!ctx || !renderer) {
        return false;
    }

    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }

    ctx->renderer = renderer;
    ctx->text_engine = TTF_CreateRendererTextEngine(renderer);
    if (!ctx->text_engine) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer text engine: %s", SDL_GetError());
        return false;
    }

    ctx->font_count = 1;
    ctx->fonts = (TTF_Font **)SDL_calloc(ctx->font_count, sizeof(TTF_Font *));
    if (!ctx->fonts) {
        TTF_DestroyRendererTextEngine(ctx->text_engine);
        ctx->text_engine = NULL;
        return false;
    }

    TTF_Font *font = NULL;
    if (font_path) {
        font = TTF_OpenFont(font_path, default_font_size);
    }

    if (!font) {
        // Fallback paths
        const char *fallback_paths[] = {
            "assets/fonts/Roboto-Regular.ttf",
            "../assets/fonts/Roboto-Regular.ttf",
            "third_party/clay/examples/SDL3-simple-demo/resources/Roboto-Regular.ttf",
            NULL
        };
        for (int i = 0; fallback_paths[i] != NULL; i++) {
            font = TTF_OpenFont(fallback_paths[i], default_font_size);
            if (font) break;
        }
    }

    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font from %s: %s", font_path ? font_path : "(null)", SDL_GetError());
        SDL_free(ctx->fonts);
        ctx->fonts = NULL;
        TTF_DestroyRendererTextEngine(ctx->text_engine);
        ctx->text_engine = NULL;
        return false;
    }

    ctx->fonts[0] = font;
    return true;
}

void Clay_SDL3_Destroy(Clay_SDL3Context *ctx) {
    if (!ctx) return;

    if (ctx->fonts) {
        for (size_t i = 0; i < ctx->font_count; i++) {
            if (ctx->fonts[i]) {
                TTF_CloseFont(ctx->fonts[i]);
            }
        }
        SDL_free(ctx->fonts);
        ctx->fonts = NULL;
    }

    if (ctx->text_engine) {
        TTF_DestroyRendererTextEngine(ctx->text_engine);
        ctx->text_engine = NULL;
    }

    TTF_Quit();
}

Clay_Dimensions Clay_SDL3_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *user_data) {
    Clay_SDL3Context *ctx = (Clay_SDL3Context *)user_data;
    if (!ctx || !ctx->fonts || config->fontId >= ctx->font_count) {
        return (Clay_Dimensions){0, 0};
    }

    TTF_Font *font = ctx->fonts[config->fontId];
    if (!font) {
        return (Clay_Dimensions){0, 0};
    }

    TTF_SetFontSize(font, config->fontSize);
    int width = 0, height = 0;
    if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
        return (Clay_Dimensions){0, 0};
    }

    return (Clay_Dimensions){ (float)width, (float)height };
}

void Clay_SDL3_Render(Clay_SDL3Context *ctx, Clay_RenderCommandArray *commands) {
    if (!ctx || !ctx->renderer || !commands) return;

    SDL_Renderer *renderer = ctx->renderer;

    for (size_t i = 0; i < commands->length; i++) {
        Clay_RenderCommand *rcmd = Clay_RenderCommandArray_Get(commands, i);
        const Clay_BoundingBox bbox = rcmd->boundingBox;
        const SDL_FRect rect = { bbox.x, bbox.y, bbox.width, bbox.height };

        switch (rcmd->commandType) {
            case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
                Clay_RectangleRenderData *config = &rcmd->renderData.rectangle;
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, (Uint8)config->backgroundColor.r, (Uint8)config->backgroundColor.g, (Uint8)config->backgroundColor.b, (Uint8)config->backgroundColor.a);
                if (config->cornerRadius.topLeft > 0) {
                    SDL_Clay_RenderFillRoundedRect(renderer, rect, config->cornerRadius.topLeft, config->backgroundColor);
                } else {
                    SDL_RenderFillRect(renderer, &rect);
                }
                break;
            }
            case CLAY_RENDER_COMMAND_TYPE_TEXT: {
                Clay_TextRenderData *config = &rcmd->renderData.text;
                if (config->fontId >= ctx->font_count || !ctx->fonts[config->fontId]) {
                    break;
                }
                TTF_Font *font = ctx->fonts[config->fontId];
                TTF_SetFontSize(font, config->fontSize);
                TTF_Text *text = TTF_CreateText(ctx->text_engine, font, config->stringContents.chars, config->stringContents.length);
                if (text) {
                    TTF_SetTextColor(text, (Uint8)config->textColor.r, (Uint8)config->textColor.g, (Uint8)config->textColor.b, (Uint8)config->textColor.a);
                    TTF_DrawRendererText(text, rect.x, rect.y);
                    TTF_DestroyText(text);
                }
                break;
            }
            case CLAY_RENDER_COMMAND_TYPE_BORDER: {
                Clay_BorderRenderData *config = &rcmd->renderData.border;
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, (Uint8)config->color.r, (Uint8)config->color.g, (Uint8)config->color.b, (Uint8)config->color.a);

                const float minRadius = SDL_min(rect.w, rect.h) / 2.0f;
                const Clay_CornerRadius clampedRadii = {
                    .topLeft = SDL_min(config->cornerRadius.topLeft, minRadius),
                    .topRight = SDL_min(config->cornerRadius.topRight, minRadius),
                    .bottomLeft = SDL_min(config->cornerRadius.bottomLeft, minRadius),
                    .bottomRight = SDL_min(config->cornerRadius.bottomRight, minRadius)
                };

                // Border lines
                if (config->width.left > 0) {
                    const float starting_y = rect.y + clampedRadii.topLeft;
                    const float length = rect.h - clampedRadii.topLeft - clampedRadii.bottomLeft;
                    SDL_FRect line = { rect.x, starting_y, (float)config->width.left, length };
                    SDL_RenderFillRect(renderer, &line);
                }
                if (config->width.right > 0) {
                    const float starting_x = rect.x + rect.w - (float)config->width.right;
                    const float length = rect.h - clampedRadii.topRight - clampedRadii.bottomRight;
                    SDL_FRect line = { starting_x, rect.y + clampedRadii.topRight, (float)config->width.right, length };
                    SDL_RenderFillRect(renderer, &line);
                }
                if (config->width.top > 0) {
                    const float starting_x = rect.x + clampedRadii.topLeft;
                    const float length = rect.w - clampedRadii.topLeft - clampedRadii.topRight;
                    SDL_FRect line = { starting_x, rect.y, length, (float)config->width.top };
                    SDL_RenderFillRect(renderer, &line);
                }
                if (config->width.bottom > 0) {
                    const float starting_x = rect.x + clampedRadii.bottomLeft;
                    const float length = rect.w - clampedRadii.bottomLeft - clampedRadii.bottomRight;
                    SDL_FRect line = { starting_x, rect.y + rect.h - (float)config->width.bottom, length, (float)config->width.bottom };
                    SDL_RenderFillRect(renderer, &line);
                }

                // Border corners
                if (config->cornerRadius.topLeft > 0) {
                    const float cx = rect.x + clampedRadii.topLeft;
                    const float cy = rect.y + clampedRadii.topLeft;
                    SDL_Clay_RenderArc(renderer, (SDL_FPoint){cx, cy}, clampedRadii.topLeft, 180.0f, 270.0f, config->width.top, config->color);
                }
                if (config->cornerRadius.topRight > 0) {
                    const float cx = rect.x + rect.w - clampedRadii.topRight;
                    const float cy = rect.y + clampedRadii.topRight;
                    SDL_Clay_RenderArc(renderer, (SDL_FPoint){cx, cy}, clampedRadii.topRight, 270.0f, 360.0f, config->width.top, config->color);
                }
                if (config->cornerRadius.bottomLeft > 0) {
                    const float cx = rect.x + clampedRadii.bottomLeft;
                    const float cy = rect.y + rect.h - clampedRadii.bottomLeft;
                    SDL_Clay_RenderArc(renderer, (SDL_FPoint){cx, cy}, clampedRadii.bottomLeft, 90.0f, 180.0f, config->width.bottom, config->color);
                }
                if (config->cornerRadius.bottomRight > 0) {
                    const float cx = rect.x + rect.w - clampedRadii.bottomRight;
                    const float cy = rect.y + rect.h - clampedRadii.bottomRight;
                    SDL_Clay_RenderArc(renderer, (SDL_FPoint){cx, cy}, clampedRadii.bottomRight, 0.0f, 90.0f, config->width.bottom, config->color);
                }
                break;
            }
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START: {
                SDL_Rect clip = {
                    (int)bbox.x,
                    (int)bbox.y,
                    (int)bbox.width,
                    (int)bbox.height
                };
                SDL_SetRenderClipRect(renderer, &clip);
                break;
            }
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END: {
                SDL_SetRenderClipRect(renderer, NULL);
                break;
            }
            case CLAY_RENDER_COMMAND_TYPE_IMAGE: {
                SDL_Texture *texture = (SDL_Texture *)rcmd->renderData.image.imageData;
                if (texture) {
                    SDL_RenderTexture(renderer, texture, NULL, &rect);
                }
                break;
            }
            default:
                break;
        }
    }
}
