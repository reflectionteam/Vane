#include "ui/renderer/clay_sdl3.h"
#include <math.h>
#include <stdlib.h>

static const int NUM_CIRCLE_SEGMENTS = 16;

static void sdl_clay_render_fill_rounded_rect(SDL_Renderer *renderer, const SDL_FRect rect,
                                              const float corner_radius,
                                              const Clay_Color color_in) {
  const SDL_FColor color = {color_in.r / 255.0f, color_in.g / 255.0f, color_in.b / 255.0f,
                            color_in.a / 255.0f};

  int index_count = 0;
  int vertex_count = 0;

  const float min_radius = SDL_min(rect.w, rect.h) / 2.0f;
  const float clamped_radius = SDL_min(corner_radius, min_radius);
  const int circle_segments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(clamped_radius * 0.5f));

  const int total_vertices = 4 + (4 * (circle_segments * 2)) + 2 * 4;
  const int total_indices = 6 + (4 * (circle_segments * 3)) + 6 * 4;

  SDL_Vertex vertices[total_vertices];
  int indices[total_indices];

  // Center rectangle
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + clamped_radius, rect.y + clamped_radius}, color, {0, 0}};
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + rect.w - clamped_radius, rect.y + clamped_radius}, color, {1, 0}};
  vertices[vertex_count++] = (SDL_Vertex){
      {rect.x + rect.w - clamped_radius, rect.y + rect.h - clamped_radius}, color, {1, 1}};
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + clamped_radius, rect.y + rect.h - clamped_radius}, color, {0, 1}};

  indices[index_count++] = 0;
  indices[index_count++] = 1;
  indices[index_count++] = 3;
  indices[index_count++] = 1;
  indices[index_count++] = 2;
  indices[index_count++] = 3;

  // Rounded corners
  const float step = (SDL_PI_F / 2.0f) / circle_segments;
  for (int i = 0; i < circle_segments; i++) {
    const float angle1 = (float)i * step;
    const float angle2 = ((float)i + 1.0f) * step;

    for (int j = 0; j < 4; j++) {
      float cx = 0;
      float cy = 0;
      float sign_x = 0;
      float sign_y = 0;

      switch (j) {
      case 0:
        cx = rect.x + clamped_radius;
        cy = rect.y + clamped_radius;
        sign_x = -1;
        sign_y = -1;
        break;
      case 1:
        cx = rect.x + rect.w - clamped_radius;
        cy = rect.y + clamped_radius;
        sign_x = 1;
        sign_y = -1;
        break;
      case 2:
        cx = rect.x + rect.w - clamped_radius;
        cy = rect.y + rect.h - clamped_radius;
        sign_x = 1;
        sign_y = 1;
        break;
      case 3:
        cx = rect.x + clamped_radius;
        cy = rect.y + rect.h - clamped_radius;
        sign_x = -1;
        sign_y = 1;
        break;
      default:
        return;
      }

      vertices[vertex_count++] = (SDL_Vertex){{cx + SDL_cosf(angle1) * clamped_radius * sign_x,
                                               cy + SDL_sinf(angle1) * clamped_radius * sign_y},
                                              color,
                                              {0, 0}};
      vertices[vertex_count++] = (SDL_Vertex){{cx + SDL_cosf(angle2) * clamped_radius * sign_x,
                                               cy + SDL_sinf(angle2) * clamped_radius * sign_y},
                                              color,
                                              {0, 0}};

      indices[index_count++] = j;
      indices[index_count++] = vertex_count - 2;
      indices[index_count++] = vertex_count - 1;
    }
  }

  // Top edge
  vertices[vertex_count++] = (SDL_Vertex){{rect.x + clamped_radius, rect.y}, color, {0, 0}};
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + rect.w - clamped_radius, rect.y}, color, {1, 0}};
  indices[index_count++] = 0;
  indices[index_count++] = vertex_count - 2;
  indices[index_count++] = vertex_count - 1;
  indices[index_count++] = 1;
  indices[index_count++] = 0;
  indices[index_count++] = vertex_count - 1;

  // Right edge
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + rect.w, rect.y + clamped_radius}, color, {1, 0}};
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + rect.w, rect.y + rect.h - clamped_radius}, color, {1, 1}};
  indices[index_count++] = 1;
  indices[index_count++] = vertex_count - 2;
  indices[index_count++] = vertex_count - 1;
  indices[index_count++] = 2;
  indices[index_count++] = 1;
  indices[index_count++] = vertex_count - 1;

  // Bottom edge
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + rect.w - clamped_radius, rect.y + rect.h}, color, {1, 1}};
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x + clamped_radius, rect.y + rect.h}, color, {0, 1}};
  indices[index_count++] = 2;
  indices[index_count++] = vertex_count - 2;
  indices[index_count++] = vertex_count - 1;
  indices[index_count++] = 3;
  indices[index_count++] = 2;
  indices[index_count++] = vertex_count - 1;

  // Left edge
  vertices[vertex_count++] =
      (SDL_Vertex){{rect.x, rect.y + rect.h - clamped_radius}, color, {0, 1}};
  vertices[vertex_count++] = (SDL_Vertex){{rect.x, rect.y + clamped_radius}, color, {0, 0}};
  indices[index_count++] = 3;
  indices[index_count++] = vertex_count - 2;
  indices[index_count++] = vertex_count - 1;
  indices[index_count++] = 0;
  indices[index_count++] = 3;
  indices[index_count++] = vertex_count - 1;

  SDL_RenderGeometry(renderer, NULL, vertices, vertex_count, indices, index_count);
}

static void sdl_clay_render_arc(SDL_Renderer *renderer, const SDL_FPoint center, const float radius,
                                const float start_angle, const float end_angle,
                                const float thickness, const Clay_Color color) {
  SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a);

  const float rad_start = start_angle * (SDL_PI_F / 180.0f);
  const float rad_end = end_angle * (SDL_PI_F / 180.0f);
  const int circle_segments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(radius * 1.5f));
  const float angle_step = (rad_end - rad_start) / (float)circle_segments;
  const float thickness_step = 0.4f;

  for (float t = thickness_step; t < thickness - thickness_step; t += thickness_step) {
    SDL_FPoint points[circle_segments + 1];
    const float clamped_radius = SDL_max(radius - t, 1.0f);

    for (int i = 0; i <= circle_segments; i++) {
      const float angle = rad_start + (float)i * angle_step;
      points[i] = (SDL_FPoint){SDL_roundf(center.x + SDL_cosf(angle) * clamped_radius),
                               SDL_roundf(center.y + SDL_sinf(angle) * clamped_radius)};
    }
    SDL_RenderLines(renderer, points, circle_segments + 1);
  }
}

bool clay_sdl3_init(Clay_SDL3Context *ctx, SDL_Renderer *renderer, const char *font_path,
                    float default_font_size) {
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
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer text engine: %s",
                 SDL_GetError());
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
    const char *fallback_paths[] = {
        "assets/fonts/GoogleSansCode-Regular.ttf",
        "../assets/fonts/GoogleSansCode-Regular.ttf",
        "assets/fonts/Roboto-Regular.ttf",
        "../assets/fonts/Roboto-Regular.ttf",
        NULL};
    for (int i = 0; fallback_paths[i] != NULL; i++) {
      font = TTF_OpenFont(fallback_paths[i], default_font_size);
      if (font) {
        break;
      }
    }
  }

  if (!font) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font from %s: %s",
                 font_path ? font_path : "(null)", SDL_GetError());
    SDL_free(ctx->fonts);
    ctx->fonts = NULL;
    TTF_DestroyRendererTextEngine(ctx->text_engine);
    ctx->text_engine = NULL;
    return false;
  }

  ctx->fonts[0] = font;
  return true;
}

void clay_sdl3_destroy(Clay_SDL3Context *ctx) {
  if (!ctx) {
    return;
  }

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

Clay_Dimensions clay_sdl3_measure_text(Clay_StringSlice text, Clay_TextElementConfig *config,
                                       void *user_data) {
  Clay_SDL3Context *ctx = (Clay_SDL3Context *)user_data;
  if (!ctx || !ctx->fonts || config->fontId >= ctx->font_count) {
    return (Clay_Dimensions){0, 0};
  }

  TTF_Font *font = ctx->fonts[config->fontId];
  if (!font) {
    return (Clay_Dimensions){0, 0};
  }

  TTF_SetFontSize(font, config->fontSize);
  int width = 0;
  int height = 0;
  if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
    return (Clay_Dimensions){0, 0};
  }

  return (Clay_Dimensions){(float)width, (float)height};
}

void clay_sdl3_render(Clay_SDL3Context *ctx, Clay_RenderCommandArray *commands) {
  if (!ctx || !ctx->renderer || !commands) {
    return;
  }

  SDL_Renderer *renderer = ctx->renderer;

  for (int32_t i = 0; i < commands->length; i++) {
    Clay_RenderCommand *rcmd = Clay_RenderCommandArray_Get(commands, i);
    const Clay_BoundingBox bbox = rcmd->boundingBox;
    const SDL_FRect rect = {bbox.x, bbox.y, bbox.width, bbox.height};

    switch (rcmd->commandType) {
    case CLAY_RENDER_COMMAND_TYPE_RECTANGLE: {
      Clay_RectangleRenderData *config = &rcmd->renderData.rectangle;
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, (Uint8)config->backgroundColor.r,
                             (Uint8)config->backgroundColor.g, (Uint8)config->backgroundColor.b,
                             (Uint8)config->backgroundColor.a);
      if (config->cornerRadius.topLeft > 0) {
        sdl_clay_render_fill_rounded_rect(renderer, rect, config->cornerRadius.topLeft,
                                          config->backgroundColor);
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
      TTF_Text *text = TTF_CreateText(ctx->text_engine, font, config->stringContents.chars,
                                      config->stringContents.length);
      if (text) {
        TTF_SetTextColor(text, (Uint8)config->textColor.r, (Uint8)config->textColor.g,
                         (Uint8)config->textColor.b, (Uint8)config->textColor.a);
        TTF_DrawRendererText(text, rect.x, rect.y);
        TTF_DestroyText(text);
      }
      break;
    }
    case CLAY_RENDER_COMMAND_TYPE_BORDER: {
      Clay_BorderRenderData *config = &rcmd->renderData.border;
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, (Uint8)config->color.r, (Uint8)config->color.g,
                             (Uint8)config->color.b, (Uint8)config->color.a);

      const float min_radius = SDL_min(rect.w, rect.h) / 2.0f;
      const Clay_CornerRadius clamped_radii = {
          .topLeft = SDL_min(config->cornerRadius.topLeft, min_radius),
          .topRight = SDL_min(config->cornerRadius.topRight, min_radius),
          .bottomLeft = SDL_min(config->cornerRadius.bottomLeft, min_radius),
          .bottomRight = SDL_min(config->cornerRadius.bottomRight, min_radius)};

      // Border lines
      if (config->width.left > 0) {
        const float starting_y = rect.y + clamped_radii.topLeft;
        const float length = rect.h - clamped_radii.topLeft - clamped_radii.bottomLeft;
        SDL_FRect line = {rect.x, starting_y, (float)config->width.left, length};
        SDL_RenderFillRect(renderer, &line);
      }
      if (config->width.right > 0) {
        const float starting_x = rect.x + rect.w - (float)config->width.right;
        const float length = rect.h - clamped_radii.topRight - clamped_radii.bottomRight;
        SDL_FRect line = {starting_x, rect.y + clamped_radii.topRight, (float)config->width.right,
                          length};
        SDL_RenderFillRect(renderer, &line);
      }
      if (config->width.top > 0) {
        const float starting_x = rect.x + clamped_radii.topLeft;
        const float length = rect.w - clamped_radii.topLeft - clamped_radii.topRight;
        SDL_FRect line = {starting_x, rect.y, length, (float)config->width.top};
        SDL_RenderFillRect(renderer, &line);
      }
      if (config->width.bottom > 0) {
        const float starting_x = rect.x + clamped_radii.bottomLeft;
        const float length = rect.w - clamped_radii.bottomLeft - clamped_radii.bottomRight;
        SDL_FRect line = {starting_x, rect.y + rect.h - (float)config->width.bottom, length,
                          (float)config->width.bottom};
        SDL_RenderFillRect(renderer, &line);
      }

      // Border corners
      if (config->cornerRadius.topLeft > 0) {
        const float cx = rect.x + clamped_radii.topLeft;
        const float cy = rect.y + clamped_radii.topLeft;
        sdl_clay_render_arc(renderer, (SDL_FPoint){cx, cy}, clamped_radii.topLeft, 180.0f, 270.0f,
                            config->width.top, config->color);
      }
      if (config->cornerRadius.topRight > 0) {
        const float cx = rect.x + rect.w - clamped_radii.topRight;
        const float cy = rect.y + clamped_radii.topRight;
        sdl_clay_render_arc(renderer, (SDL_FPoint){cx, cy}, clamped_radii.topRight, 270.0f, 360.0f,
                            config->width.top, config->color);
      }
      if (config->cornerRadius.bottomLeft > 0) {
        const float cx = rect.x + clamped_radii.bottomLeft;
        const float cy = rect.y + rect.h - clamped_radii.bottomLeft;
        sdl_clay_render_arc(renderer, (SDL_FPoint){cx, cy}, clamped_radii.bottomLeft, 90.0f, 180.0f,
                            config->width.bottom, config->color);
      }
      if (config->cornerRadius.bottomRight > 0) {
        const float cx = rect.x + rect.w - clamped_radii.bottomRight;
        const float cy = rect.y + rect.h - clamped_radii.bottomRight;
        sdl_clay_render_arc(renderer, (SDL_FPoint){cx, cy}, clamped_radii.bottomRight, 0.0f, 90.0f,
                            config->width.bottom, config->color);
      }
      break;
    }
    case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START: {
      SDL_Rect clip = {(int)bbox.x, (int)bbox.y, (int)bbox.width, (int)bbox.height};
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
