#include "ui/renderer/svg_loader.h"

#include <cairo.h>
#include <librsvg/rsvg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SDL_Texture *svg_loader_render(SDL_Renderer *renderer, const char *filepath, int width, int height,
                               SvgColorMode color_mode) {
  if (!renderer || !filepath || width <= 0 || height <= 0) {
    return NULL;
  }

  GError *error = NULL;
  RsvgHandle *handle = rsvg_handle_new_from_file(filepath, &error);
  if (!handle) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load SVG %s: %s", filepath,
                 error ? error->message : "unknown error");
    if (error) {
      g_error_free(error);
    }
    return NULL;
  }

  cairo_surface_t *cairo_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  if (cairo_surface_status(cairo_surface) != CAIRO_STATUS_SUCCESS) {
    g_object_unref(handle);
    return NULL;
  }

  cairo_t *cr = cairo_create(cairo_surface);
  RsvgRectangle viewport = {.x = 0.0, .y = 0.0, .width = (double)width, .height = (double)height};

  if (!rsvg_handle_render_document(handle, cr, &viewport, &error)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render SVG %s: %s", filepath,
                 error ? error->message : "unknown error");
    if (error) {
      g_error_free(error);
    }
  }

  cairo_destroy(cr);
  cairo_surface_flush(cairo_surface);

  int stride = cairo_image_surface_get_stride(cairo_surface);
  uint8_t *data = cairo_image_surface_get_data(cairo_surface);

  if (color_mode == SVG_COLOR_WHITE) {
    for (int y = 0; y < height; y++) {
      uint32_t *row = (uint32_t *)(data + y * stride);
      for (int x = 0; x < width; x++) {
        uint32_t pixel = row[x];
        uint32_t alpha = (pixel >> 24) & 0xFF;
        if (alpha > 0) {
          // Premultiplied ARGB for white: A=alpha, R=alpha, G=alpha, B=alpha
          row[x] = (alpha << 24) | (alpha << 16) | (alpha << 8) | alpha;
        } else {
          row[x] = 0;
        }
      }
    }
  } else if (color_mode == SVG_COLOR_BLACK) {
    for (int y = 0; y < height; y++) {
      uint32_t *row = (uint32_t *)(data + y * stride);
      for (int x = 0; x < width; x++) {
        uint32_t pixel = row[x];
        uint32_t alpha = (pixel >> 24) & 0xFF;
        if (alpha > 0) {
          // Premultiplied ARGB for black: A=alpha, R=0, G=0, B=0
          row[x] = (alpha << 24);
        } else {
          row[x] = 0;
        }
      }
    }
  }

  SDL_Surface *sdl_surface =
      SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_ARGB8888, data, stride);
  if (!sdl_surface) {
    cairo_surface_destroy(cairo_surface);
    g_object_unref(handle);
    return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
  if (texture) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }

  SDL_DestroySurface(sdl_surface);
  cairo_surface_destroy(cairo_surface);
  g_object_unref(handle);

  return texture;
}

static void build_asset_path(char *dst, size_t dst_size, const char *base_path, const char *rel) {
  if (base_path && strlen(base_path) > 0) {
    snprintf(dst, dst_size, "%sassets/svg/%s", base_path, rel);
  } else {
    snprintf(dst, dst_size, "assets/svg/%s", rel);
  }
}

bool svg_loader_init(SvgIconCache *cache, SDL_Renderer *renderer, const char *assets_base_path) {
  if (!cache || !renderer) {
    return false;
  }

  memset(cache, 0, sizeof(*cache));

  char path[512];

  // 1. Sidebar tab icons: 18x18
  build_asset_path(path, sizeof(path), assets_base_path, "overview.svg");
  cache->overview_white = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_WHITE);
  cache->overview_black = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_BLACK);

  build_asset_path(path, sizeof(path), assets_base_path, "mods.svg");
  cache->mods_white = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_WHITE);
  cache->mods_black = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_BLACK);

  build_asset_path(path, sizeof(path), assets_base_path, "servers.svg");
  cache->servers_white = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_WHITE);
  cache->servers_black = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_BLACK);

  build_asset_path(path, sizeof(path), assets_base_path, "screenshots.svg");
  cache->screenshots_white = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_WHITE);
  cache->screenshots_black = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_BLACK);

  build_asset_path(path, sizeof(path), assets_base_path, "logs.svg");
  cache->logs_white = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_WHITE);
  cache->logs_black = svg_loader_render(renderer, path, 18, 18, SVG_COLOR_BLACK);

  // 2. Header assets
  build_asset_path(path, sizeof(path), assets_base_path, "vane.svg");
  cache->logo = svg_loader_render(renderer, path, 24, 24, SVG_COLOR_ORIGINAL);

  build_asset_path(path, sizeof(path), assets_base_path, "settings.svg");
  cache->settings = svg_loader_render(renderer, path, 15, 15, SVG_COLOR_ORIGINAL);

  // 3. Chevrons: 16x16
  build_asset_path(path, sizeof(path), assets_base_path, "chevron-left.svg");
  cache->chevron_left = svg_loader_render(renderer, path, 16, 16, SVG_COLOR_WHITE);

  build_asset_path(path, sizeof(path), assets_base_path, "chevron-right.svg");
  cache->chevron_right = svg_loader_render(renderer, path, 16, 16, SVG_COLOR_WHITE);

  build_asset_path(path, sizeof(path), assets_base_path, "chevron-up.svg");
  cache->chevron_up = svg_loader_render(renderer, path, 16, 16, SVG_COLOR_WHITE);

  return true;
}

void svg_loader_destroy(SvgIconCache *cache) {
  if (!cache) {
    return;
  }

  if (cache->overview_white) SDL_DestroyTexture(cache->overview_white);
  if (cache->overview_black) SDL_DestroyTexture(cache->overview_black);
  if (cache->mods_white) SDL_DestroyTexture(cache->mods_white);
  if (cache->mods_black) SDL_DestroyTexture(cache->mods_black);
  if (cache->servers_white) SDL_DestroyTexture(cache->servers_white);
  if (cache->servers_black) SDL_DestroyTexture(cache->servers_black);
  if (cache->screenshots_white) SDL_DestroyTexture(cache->screenshots_white);
  if (cache->screenshots_black) SDL_DestroyTexture(cache->screenshots_black);
  if (cache->logs_white) SDL_DestroyTexture(cache->logs_white);
  if (cache->logs_black) SDL_DestroyTexture(cache->logs_black);
  if (cache->logo) SDL_DestroyTexture(cache->logo);
  if (cache->settings) SDL_DestroyTexture(cache->settings);
  if (cache->chevron_left) SDL_DestroyTexture(cache->chevron_left);
  if (cache->chevron_right) SDL_DestroyTexture(cache->chevron_right);
  if (cache->chevron_up) SDL_DestroyTexture(cache->chevron_up);

  memset(cache, 0, sizeof(*cache));
}
