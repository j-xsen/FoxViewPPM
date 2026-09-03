#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>

#include "ppm.h"

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  const char *window_title;
  int screen_width;
  int screen_height;
  Uint32 render_flags;
  float zoom;
  float pan_x;
  float pan_y;
} CustomRenderer;

#define ZOOM_MIN 0.1f
#define ZOOM_MAX 10.0f
#define ZOOM_STEP 0.1f

int initialize_renderer(CustomRenderer *renderer, const char *window_title,
                        const int window_width, const int window_height,
                        Uint32 flags);

void draw(CustomRenderer *renderer);
void terminate_renderer(CustomRenderer *renderer);